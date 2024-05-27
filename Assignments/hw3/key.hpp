/* key.hpp ---
 *
 * Filename: key.hpp
 * Description:
 * Author: Adeel Bhutta
 * Maintainer:
 * Created: Thu Sep 15 16:36:21 2016
 * Last-Updated:
 *           By:
 *     Update #: 0
 * Keywords:
 * Compatibility:
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change log:
 *
 *
 */

/* Copyright (c) 2016  Adeel Bhutta
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */

#ifndef KEY_H
#define KEY_H

#include <cstdbool>

/*
 * @enum KEYS
 * @brief This enum represents the keys that can be pressed.
 */
enum
{
    NOCHAR,  /**< No character */
    REGCHAR, /**< Regular character */
    UP,      /**< Up arrow key */
    DOWN,    /**< Down arrow key */
    LEFT,    /**< Left arrow key */
    RIGHT,   /**< Right arrow key */
    BADESC,  /**< Bad escape character */
    W,       /**< W key */
    A,       /**< A key */
    S,       /**< S key */
    D,       /**< D key */
    P,       /**< P key */
    Q        /**< Q key */
};

/*
 * @brief This function reads the escape key.
 *
 * @param key: The key to read.
 *
 * @return int: The key.
 */
int read_escape(int *);

/* key.hpp ends here */

#endif
