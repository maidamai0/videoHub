#pragma once

enum class ContentType { kDownloading, kDownloaded };

class State {
   public:
    static auto& GetInstance() {
        static State instance;
        return instance;
    }

    auto GetContentType() {
        return content_type_;
    }

    auto SetContentType(const ContentType type) {
        content_type_ = type;
    }

   private:
    State() = default;

    ContentType content_type_{ContentType::kDownloading};
};