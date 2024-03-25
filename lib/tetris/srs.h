/**
 * @file srs.h
 * @brief Defines the Super Rotation System (SRS) offsets and provides functions for Tetris piece rotations.
 *
 * This header file includes the definitions of the SRS offsets for rotating Tetris pieces according to the
 * Super Rotation System (SRS). It contains arrays of offsets for each rotation state and functions to retrieve these
 * offsets depending on the piece type and its current rotation. Each offset array corresponds to the priority with
 * which each offset is applied during a rotation attempt. The system checks for each offset in order to find a valid
 * piece placement (also known as a "kick"). The first offset that allows for a valid placement will be applied to
 * perform the rotation.
 */

#include "stdint.h"
#include "TETRIS_ENUMS.h"

#ifndef SRS
#define SRS 


/**
 * @struct SRSOffest
 * @brief Structure representing an offset for piece rotation.
 * 
 * This structure defines an offset by specifying the horizontal (x) and vertical (y) displacement.
 * Offsets are used to attempt piece rotations according to the Super Rotation System, where the first
 * valid offset for placement is the one applied (also referred to as a kick).
 */
struct SRSOffest {
    int8_t offsetx;
    int8_t offsety;
};

/**
 * @brief SRS offsets for a 180-degree rotation with priority.
 * 
 * Defines the offsets used for rotating a piece 180 degrees, ordered by the priority of their application.
 * The system checks each offset for a valid piece placement, applying the first one that allows the piece
 * to fit.
 */
const SRSOffest offsets180[4][6] =  {
    {{0, 0}, {0, -1}, {1, -1}, {-1, -1}, {1, 0}, {-1, 0}},
    {{0, 0}, {1, 0}, {1, -2}, {1,-1}, {0, -2}, {0, -1}},
    {{0, 0}, {0, 1}, {-1, 1}, {1, 1}, {-1, 0}, {1, 0}},
    {{0, 0}, {-1, 0}, {-1, -2}, {-1, -1}, {0, -2}, {0, -1}}
};

/**
 * @brief SRS offsets for a 90-degree rotation with priority.
 * 
 * Defines the offsets used for rotating a piece 90 degrees clockwise, ordered by the priority of their application.
 * The system checks each offset for a valid piece placement, applying the first one that allows the piece
 * to fit.
 */
const SRSOffest offsets90[4][5] = {
    {{0, 0},{-1, 0},{-1, -1},{0, 2},{-1, 2}},
    {{0, 0},{1, 0},{1, 1},{0, -2},{1, -2}},
    {{0, 0},{1, 0},{1, -1},{0, 2},{1, 2}},
    {{0, 0},{-1, 0},{-1, 1},{0, -2},{-1, -2}}
};

/**
 * @brief SRS offsets for a 270-degree rotation with priority.
 * 
 * Defines the offsets used for rotating a piece 270 degrees clockwise (or 90 degrees counterclockwise),
 * ordered by the priority of their application. The system checks each offset for a valid piece placement,
 * applying the first one that allows the piece to fit.
 */
const SRSOffest offsets270[4][5] = {
    {{0, 0},{1, 0},{1, -1},{0, 2},{1, 2}},
    {{0, 0},{1, 0},{1, 1},{0, -2},{1, -2}},
    {{0, 0},{-1, 0},{-1, -1},{0, 2},{-1, 2}},
    {{0, 0},{-1, 0},{-1, 1},{0, -2},{-1, -2}}
};

/**
 * @brief SRS offsets for the "I" piece for a 90-degree rotation with priority.
 * 
 * Special offsets for the "I" piece when rotating it 90 degrees clockwise, ordered by the priority of
 * their application. These account for its unique behavior in the SRS system, with each offset checked
 * for a valid placement and the first valid one applied.
 */
const SRSOffest offsetsI90[4][5] = {
    {{0, 0},{1, 0},{-2, 0},{-2, 1},{1, -2}},
    {{0, 0},{-1, 0},{2, 0},{-1, -2},{2, 1}},
    {{0, 0},{2, 0},{-1, 0},{2, -1},{-1, 2}},
    {{0, 0},{1, 0},{-2, 0},{1, -2},{-2, -1}}
};

/**
 * @brief SRS offsets for the "I" piece for a 270-degree rotation with priority.
 * 
 * Special offsets for the "I" piece when rotating it 270 degrees clockwise (or 90 degrees counterclockwise),
 * ordered by the priority of their application. These account for its unique behavior in the SRS system,
 * with each offset checked for a valid placement and the first valid one applied.
 */
const SRSOffest offsetsI270[4][5] = {
    {{0, 0},{-1, 0},{2, 0},{2, 1},{-1, -2}},
    {{0, 0},{-1, 0},{2, 0},{-1, -2},{2, 1}},
    {{0, 0},{-2, 0},{1, 0},{-2, -1},{1, 2}},
    {{0, 0},{1, 0},{-2, 0},{1, -2},{-2, 1}}
};


/**
 * @brief Retrieves SRS offsets based on piece type and rotation with priority consideration.
 * 
 * Determines the appropriate SRS offsets to use when rotating a piece from its current
 * orientation to a new orientation, based on the piece type, the intended rotation direction,
 * and the priority of offset application. The first offset that allows for a valid placement
 * (kick) will be applied to perform the rotation.
 * 
 * @param type The type of the Tetris piece being rotated.
 * @param currentRotation The current orientation of the piece.
 * @param rotation The intended rotation direction.
 * @param offsetAmount A pointer to an integer to store the number of offsets checked.
 * @return A pointer to the SRSOffsets array of applicable offsets with priority.
 */
SRSOffest* getSRSOffsetsFromTypeAndRotation(PieceType type, Rotation currentRotation, Rotation rotation, int* offsetAmount); 

#endif