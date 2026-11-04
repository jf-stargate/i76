#include "i76/shell_frontends.h"

#include <SDL3/SDL.h>

#include <cstdint>
#include <iostream>
#include <string>

static void shell_sdl_process_key(i76_shell_state& shell, i76_runtime& game, SDL_Keycode key)
{
    i76_shell_view view = i76_shell_make_view(shell);
    std::uint32_t index = 0;

    if (key == SDLK_UP) {
        if (view.item_count != 0U) {
            shell.selected_index = (shell.selected_index + view.item_count - 1U) % view.item_count;
        }
        return;
    }
    if (key == SDLK_DOWN) {
        if (view.item_count != 0U) {
            shell.selected_index = (shell.selected_index + 1U) % view.item_count;
        }
        return;
    }
    if (key == SDLK_ESCAPE) {
        if (shell.page == i76_shell_page::main_menu) {
            i76_shell_execute(shell, game, "exit");
        } else {
            i76_shell_execute(shell, game, "back");
        }
        return;
    }
    if (key == SDLK_RETURN || key == SDLK_KP_ENTER) {
        i76_shell_select(shell, game, shell.selected_index);
        return;
    }
    if (key >= SDLK_1 && key <= SDLK_8) {
        index = static_cast<std::uint32_t>(key - SDLK_1);
        i76_shell_select(shell, game, index);
    }
}

static bool shell_sdl_present(SDL_Renderer* renderer, const i76_shell_state& shell,
                              const i76_runtime& game)
{
    i76_shell_view view = i76_shell_make_view(shell);
    SDL_FRect highlight = {};
    std::uint32_t index = 0;
    float y = 0.0f;
    std::string title{view.title};
    std::string subtitle{view.subtitle};
    std::string status = {};
    std::string label = {};

    status = "tick " + std::to_string(game.state.tick) + " | " +
             (game.state.paused ? "PAUSED" : "READY") + " | Esc: back/exit";

    SDL_SetRenderDrawColor(renderer, 20U, 23U, 28U, 255U);
    if (!SDL_RenderClear(renderer)) {
        return false;
    }
    SDL_SetRenderDrawColor(renderer, 229U, 183U, 111U, 255U);
    SDL_RenderDebugText(renderer, 28.0f, 24.0f, title.c_str());
    SDL_SetRenderDrawColor(renderer, 170U, 182U, 196U, 255U);
    SDL_RenderDebugText(renderer, 28.0f, 44.0f, subtitle.c_str());

    for (index = 0; index < view.item_count; ++index) {
        y = 80.0f + static_cast<float>(index) * 20.0f;
        if (index == shell.selected_index) {
            highlight = {20.0f, y - 5.0f, 440.0f, 18.0f};
            SDL_SetRenderDrawColor(renderer, 55U, 63U, 72U, 255U);
            SDL_RenderFillRect(renderer, &highlight);
            SDL_SetRenderDrawColor(renderer, 255U, 215U, 135U, 255U);
        } else {
            SDL_SetRenderDrawColor(renderer, 225U, 230U, 235U, 255U);
        }
        label = std::to_string(index + 1U) + ". " + std::string(view.items[index].label);
        SDL_RenderDebugText(renderer, 32.0f, y, label.c_str());
    }

    SDL_SetRenderDrawColor(renderer, 150U, 166U, 180U, 255U);
    SDL_RenderDebugText(renderer, 28.0f, 230.0f, status.c_str());
    if (!shell.notice.empty()) {
        SDL_RenderDebugText(renderer, 28.0f, 246.0f, shell.notice.c_str());
    }
    return SDL_RenderPresent(renderer);
}

std::int32_t i76_run_sdl_shell(i76_shell_state& shell, i76_runtime& game,
                               std::uint32_t maximum_frames)
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event = {};
    bool video_initialized = false;
    bool window_created = false;
    std::int32_t result = 0;
    std::uint32_t frames = 0;

    if (!shell.initialized || !game.state.initialized) {
        return 1;
    }
    video_initialized = SDL_Init(SDL_INIT_VIDEO);
    if (!video_initialized) {
        std::cerr << "SDL video initialization failed: " << SDL_GetError() << '\n';
        return 1;
    }
    window_created = SDL_CreateWindowAndRenderer("Interstate '76 | Reconstruction", 960, 540,
                                                  SDL_WINDOW_RESIZABLE, &window, &renderer);
    if (!window_created) {
        std::cerr << "SDL window creation failed: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }
    SDL_SetRenderScale(renderer, 2.0f, 2.0f);

    while (!game.state.exit_requested) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                i76_shell_execute(shell, game, "exit");
            } else if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat) {
                shell_sdl_process_key(shell, game, event.key.key);
            }
        }
        if (game.state.exit_requested) {
            break;
        }
        if (!shell_sdl_present(renderer, shell, game)) {
            std::cerr << "SDL shell presentation failed: " << SDL_GetError() << '\n';
            result = 1;
            break;
        }
        ++frames;
        if (maximum_frames != 0U && frames >= maximum_frames) {
            break;
        }
        SDL_Delay(16U);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return result;
}
