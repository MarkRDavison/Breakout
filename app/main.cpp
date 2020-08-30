#include <zeno/Core.hpp>
#include <zeno/Game.hpp>
#include <Definitions.hpp>
#include <Scenes/GameScene.hpp>
#include <Scenes/IntroScene.hpp>
#include <Scenes/TitleScene.hpp>
#include <memory>

struct FontData {
	FontData(
		const std::string& _name, 
		const std::string& _path) 
	:
		name(_name), 
		path(_path) {
	}
	const std::string name;
	const std::string path;
};

struct TextureData {
	TextureData(
		const std::string& _name,
		const std::string& _path)
	:
		name(_name),
		path(_path) {
	}
	const std::string name;
	const std::string path;
};

struct ShaderData {
	ShaderData(
		const std::string& _name,
		const std::string& _vertexPath,
		const std::string& _fragmentPath,
		const std::vector<std::string>& _uniforms)
	:
		name(_name),
		vertexPath(_vertexPath),
		fragmentPath(_fragmentPath),
		uniforms(_uniforms) {
	}

	const std::string name;
	const std::string vertexPath;
	const std::string fragmentPath;
	const std::vector<std::string> uniforms;
};

int main(int _argc, char** _argv) {
	srand((unsigned)time(nullptr));

	ze::Logger logger(std::cout, ze::Severity::Trace);
	ze::Application app;
	ze::VideoMode mode = ze::VideoMode(1920, 1080, brk::Definitions::Title);
	mode.vsync = true;
	ze::SceneTransitionManager sceneTransitionManager([&app]() -> void { app.stop(); });

	if (!app.initialise(mode)) {
		logger.log(ze::Severity::Error, "Failed to initialize application");
		return EXIT_FAILURE;
	}

	ze::FontManager fontManager;
	ze::TextureManager textureManager;
	ze::ShaderManager shaderManager;
	ze::InputManager inputManager(app.getWindow());
	ze::InputActionManager inputActionManager(inputManager);

	logger.log(ze::Severity::Info, "Registering Actions");

	{
		{
			ze::InputAction action;
			action.primaryActivationType = ze::InputAction::InputActivationType::KeyPress;
			action.primaryKey = ze::Keyboard::Key::Space;
			inputActionManager.registerAction("Launch", action);
		}
		{
			ze::InputAction action;
			action.primaryActivationType = ze::InputAction::InputActivationType::KeyHold;
			action.primaryKey = ze::Keyboard::Key::Left;
			action.secondaryActivationType = ze::InputAction::InputActivationType::KeyHold;
			action.secondaryKey = ze::Keyboard::Key::A;
			inputActionManager.registerAction("Left", action);
		}
		{
			ze::InputAction action;
			action.primaryActivationType = ze::InputAction::InputActivationType::KeyHold;
			action.primaryKey = ze::Keyboard::Key::Right;
			action.secondaryActivationType = ze::InputAction::InputActivationType::KeyHold;
			action.secondaryKey = ze::Keyboard::Key::D;
			inputActionManager.registerAction("Right", action);
		}
	}

	logger.log(ze::Severity::Info, "Loading Resources");

	const std::vector<FontData> fontData = {
		FontData(brk::Definitions::Font_Midazzle_Name, "./data/font/MidazzleDemoRegular.ttf")
	};
	for (const auto& d : fontData) {
		if (!fontManager.loadFont(d.path, d.name, 128)) {
			logger.log(ze::Severity::Fatal, "Failed to load font '%' at '%'", d.name, d.path);
			return EXIT_FAILURE;
		}
	}

	const std::vector<TextureData> textureData = {

	};
	for (const auto& d : textureData) {
		if (!textureManager.loadTexture(d.path, d.name)) {
			logger.log(ze::Severity::Fatal, "Failed to load texture '%' at '%'", d.name, d.path);
			return EXIT_FAILURE;
		}
	}

	const std::vector<ShaderData> shaderData = {
		ShaderData(brk::Definitions::Shader_Name_Sprite, "./data/shader/sprite.vertex.glsl", "./data/shader/sprite.fragment.glsl", { "model", "view", "projection" })
	};
	for (const auto& d : shaderData) {
		if (!shaderManager.loadShader(d.vertexPath, d.fragmentPath, d.name, d.uniforms)) {
			logger.log(ze::Severity::Fatal, "Failed to load shader '%' at '%' / '%'", d.name, d.vertexPath, d.fragmentPath);
			return EXIT_FAILURE;
		}
	}


	logger.log(ze::Severity::Trace, "Registering Scenes");

	std::shared_ptr<brk::IntroScene> intro;
	std::shared_ptr<brk::TitleScene> title;
	std::shared_ptr<brk::GameScene> game;

	brk::Definitions::IntroSceneId = ze::SceneTransitionManager::registerState();
	{
		sceneTransitionManager.registerSceneTransition(brk::Definitions::IntroSceneId, [&]() -> void {
			intro = std::make_shared<brk::IntroScene>(
				logger,
				sceneTransitionManager);
			app.setScene(intro.get());
		});
	}
	brk::Definitions::TitleSceneId = ze::SceneTransitionManager::registerState();
	{
		sceneTransitionManager.registerSceneTransition(brk::Definitions::TitleSceneId, [&]() -> void {
			title = std::make_shared<brk::TitleScene>(
				logger,
				sceneTransitionManager);
			app.setScene(title.get());
		});
	}
	brk::Definitions::GameSceneId = ze::SceneTransitionManager::registerState();
	{
		sceneTransitionManager.registerSceneTransition(brk::Definitions::GameSceneId, [&]() -> void {
			game = std::make_shared<brk::GameScene>(
				logger,
				sceneTransitionManager,
				inputManager,
				inputActionManager);
			game->initialize();
			app.setScene(game.get());
		});
	}

	logger.log(ze::Severity::Info, "Starting application");

	sceneTransitionManager.pushSceneTransition(brk::Definitions::GameSceneId);

	app.start();

	logger.log(ze::Severity::Info, "Exiting application");

	return EXIT_SUCCESS;
}