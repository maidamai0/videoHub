#include "database.h"

#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <type_traits>

#include "logger.h"
#include "nlohmann/json_fwd.hpp"
#include "task_store.hpp"

constexpr auto kDataBaseFileName = "video_hub_data.json";
constexpr auto kSettingsKey = "settings";
constexpr auto kDownloadingTaskKey = "downloading_tasks";
constexpr auto kDownloadedTaskKey = "downloaded_tasks";
constexpr auto kTaskUrlKey = "url";
constexpr auto kTaskPathKey = "path";
constexpr auto kFontPathKey = "font_path";
constexpr auto kLogLevelKey = "log_level";

void Database::Save() {
    nlohmann::json database;
    // settings
    database[kSettingsKey] = nlohmann::json::object();
    database[kSettingsKey][kFontPathKey] = font_path_;
    database[kSettingsKey][kLogLevelKey] = log_level_;

    const auto save_task = [&database](std::string&& task_key, const auto task) {
        nlohmann::json task_json;
        task_json[kTaskUrlKey] = task->GetUrl();
        task_json[kTaskPathKey] = task->GetFullPath();
        database[task_key].emplace_back(std::move(task_json));
    };

    // save downloading tasks
    database[kDownloadingTaskKey] = nlohmann::json::array();
    for (const auto& task : TaskStore::GetInstance().GetDownloadingList()) {
        save_task(kDownloadingTaskKey, task);
    }

    // save downloading tasks
    database[kDownloadingTaskKey] = nlohmann::json::array();
    for (const auto& task : TaskStore::GetInstance().GetDownloadedList()) {
        save_task(kDownloadedTaskKey, task);
    }

    // flush to file
    std::ofstream file(kDataBaseFileName);
    file << std::setw(4) << database;
}

void Database::Load() {
    try {
        std::ifstream file(kDataBaseFileName);
        if (!file.is_open()) {
            LOG_W("no data base found");
            return;
        }

        nlohmann::json database;
        file >> database;

        // restore seettings
        font_path_ = database[kSettingsKey][kFontPathKey];
        log_level_ = database[kSettingsKey][kLogLevelKey];

        Logger::GetInstance().SetLevel(GetLogLevel());
        LOG_I("log level set to {}", log_level_);

        // restore downloading task
        for (const auto& task_json : database[kDownloadingTaskKey]) {
            TaskStore::GetInstance().GetPendingList().Push(task_json[kTaskUrlKey]);
        }

        // restore downloaded task
        for (const auto& task_json : database[kDownloadedTaskKey]) {
            auto task = std::make_shared<Task>(task_json[kTaskUrlKey]);
            task->SetFullPath(task_json[kTaskPathKey]);
            TaskStore::GetInstance().AddDownloadedTask(task);
        }
    } catch (const nlohmann::json::exception& e) {
        LOG_W("Load database failed:{}", e.what());
    }
}