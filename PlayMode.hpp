#include "Mode.hpp"

#include "Scene.hpp"
#include "WalkMesh.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>
#include <ctime>
#include <stack>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;
	Scene::Transform *jelly = nullptr;
	Scene::Transform *player_body = nullptr;

	// initialize on every stage
	glm::uvec3 player_start_at;
	uint8_t stepped_over = 0;
	std::stack<glm::vec3> jelly_positions;

	int score = 2;
	bool player_dead = false;

	int state = 0;
	int level = 0;

	void level_up();
	bool check_collision();

	std::string display_str = "Score: 0 | Level: 1 ";

		// player info:
		struct Player
	{
		WalkPoint at;
		//transform is at player's feet and will be yawed by mouse left/right motion:
		Scene::Transform *transform = nullptr;
		//camera is at player's head and will be pitched by mouse up/down motion:
		Scene::Camera *camera = nullptr;
	} player, jelly_player;
};
