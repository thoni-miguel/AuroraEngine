#pragma once

#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Events/Event.h"

namespace fmt {
    template <>
    struct formatter<Aurora::Event> {
        constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
            return ctx.end();
        }

        template <typename FormatContext>
        auto format(const Aurora::Event& e, FormatContext& ctx) -> decltype(ctx.out()) {
            return fmt::format_to(ctx.out(), "{}", e.toString());
        }
    };
}
