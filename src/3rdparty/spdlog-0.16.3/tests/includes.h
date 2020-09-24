#pragma once

#include <cstdio>
#include <fstream>
#include <string>
#include <ostream>
#include <chrono>
#include <exception>
#include "catch.hpp"
#include "utils.h"

#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON

#include <spdlog/spdlog.h>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/ostream_sink.h>

