#include "SkeletonRenderer.hpp"

namespace skeleton {
SkeletonRenderer::SkeletonRenderer() {
	this->window = nullptr;
	this->renderer = nullptr;
	this->asset_manager = new AssetManager();
	logger->log("Created Renderer Service");
}

SkeletonRenderer::SkeletonRenderer(std::string title, int width, int height,
								   bool debug_mode) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}

	SDL_Window *window = SDL_CreateWindow(
		title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
		height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	SDL_Renderer *renderer =
		SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (debug_mode) {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO &io{ImGui::GetIO()};
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
		ImGui_ImplSDLRenderer2_Init(renderer);
	}

	this->debug_mode = debug_mode;
	this->window = window;
	this->renderer = renderer;
	this->asset_manager = new AssetManager();
	logger->log("Created Renderer Service");
}

SkeletonRenderer::~SkeletonRenderer() {
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
	delete this->asset_manager;
	logger->log("Destroyed Renderer service");
}

void SkeletonRenderer::begin() {
	if (this->debug_mode) {
		// Start the Dear ImGui frame
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}
	SDL_SetRenderDrawColor(this->renderer, 125, 125, 125, 255);
	SDL_RenderClear(this->renderer);
}

void SkeletonRenderer::end() {
	if (this->debug_mode) {
		ImGui::Render();
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
	}
	SDL_RenderPresent(this->renderer);
}

void SkeletonRenderer::shutdown() {
	if (this->debug_mode) {
		ImGui_ImplSDLRenderer2_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

void SkeletonRenderer::add_texture(std::string file_path, std::string name) {
	this->asset_manager->add_texture(file_path, name, this->renderer);
}

SDL_Texture *SkeletonRenderer::get_texture(std::string name) {
	return this->asset_manager->get_texture(name);
}

void SkeletonRenderer::draw_texture(std::string name, SDL_Rect clip, int x,
									int y) {

	SDL_RenderCopy(this->renderer, asset_manager->get_texture(name), nullptr,
				   nullptr);
}

void SkeletonRenderer::draw_rect(int x, int y, int w, int h, int r, int g,
								 int b, int a) {
	SDL_Rect rect = {x, y, w, h};
	SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
	SDL_RenderFillRect(this->renderer, &rect);
}

int SkeletonRenderer::get_window_width() {
	int w, h;
	SDL_GetWindowSize(this->window, &w, &h);
	return w;
}

int SkeletonRenderer::get_window_height() {
	int w, h;
	SDL_GetWindowSize(this->window, &w, &h);
	return h;
}

void SkeletonRenderer::set_clear_color(SDL_Color color) {
	SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
}

void SkeletonRenderer::set_debug_mode(bool debug_mode) {
	this->debug_mode = debug_mode;
}
void SkeletonRenderer::draw_scene() {}
} // namespace skeleton