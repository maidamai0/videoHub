#pragma once

/**
 * @file configuration.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief   configuration model of video_hub, proxy of confugration file and ui
 * @version 0.1
 * @date 2020-03-07
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <string>

#include "common/global_def.h"

class VH_API Config {
   public:
    Config();
    void Print();

   private:
    std::string http_proxy_;
    std::string https_proxy_;
};
