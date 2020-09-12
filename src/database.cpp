#include "database.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <type_traits>

#include "nlohmann/json_fwd.hpp"
#include "task_store.hpp"

constexpr auto kDataBaseFileName = "video_hub_data.json";
constexpr auto kSettingsKey = "settings";
constexpr auto kDownloadingTaskKey = "downloading_tasks";
constexpr auto kDownloadedTaskKey = "downloaded_tasks";
constexpr auto kTaskUrlKey = "url";
constexpr auto kTaskPathKey = "path";

void Database::Save() {
    nlohmann::json database;
    // settings
    database[kSettingsKey] = nlohmann::json::object();

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
    for (const auto& task : TaskStore::GetInstance().GetDownloadedList()) {
        save_task(kDownloadedTaskKey, task);
    }

    // flush to file
    std::ofstream file(kDataBaseFileName);
    file << database;
}

void Database::Load() {
    std::ifstream file(kDataBaseFileName);
    if (!file.is_open()) {
        std::cout << "no data base found" << std::endl;
        return;
    }

    nlohmann::json database;
    file >> database;

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
}