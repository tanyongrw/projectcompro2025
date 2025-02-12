#include "Animate.h"

static Animation animate;

sf::IntRect GetGhostFrame(GhostType type, TargetState state, Dir dir)
{
	sf::IntRect ghost = { 0,128,32,32 };

	int offset = 0;
	if (state != FRIGHTENED) {
		switch (dir)
		{
		case UP:
			offset = 128;
			break;
		case DOWN:
			offset = 128 + 64;
			break;
		case LEFT:
			offset = 64;
			break;
		}
	}
	
	if (state == FRIGHTENED) {
		ghost.left = 256;
		if (animate.fright_flash)
			ghost.left += 64;
	}
	else if (state == GOHOME || state == ENTERHOME) {
		ghost.left = 256 + (offset/2);
		ghost.top = 128 + 32;
	}
	else {
		ghost.top += 32 * type;
		ghost.left = offset;
	}
	if(state != GOHOME && state != ENTERHOME)
		ghost.left += animate.ghost_frame_2 * 32;

	return ghost;
}
