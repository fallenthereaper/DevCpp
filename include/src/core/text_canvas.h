#pragma once

#include <iostream>
#include "src/core/utils/utility.h"

using Vec2 = Utility::Mth::Vec2;


namespace GameRenderer {

    class TextCanvas {
    public:
        // Constructor to initialize the canvas with given width and height
        TextCanvas(int width, int height);

        // Destructor to free dynamically allocated memory
        ~TextCanvas();

        // Clear the canvas by setting all cells to empty (' ')
        void clear();

        // Set a character at a specified position on the canvas
        void setChar(const Vec2& pos, char ch);

        // Draw a line on the canvas from start to end with specified character
        void drawLine(const Vec2& start, const Vec2& end, char ch);

        void drawSquare(const Vec2& topLeft, int width, int height, char ch, const std::string& buttonText = "", bool hollow = false);

        void drawCircle(const Vec2& center, int radius, char ch, bool hollow = false);

        void drawText(const Vec2& pos, const std::string& text);

        // Set a character at a specified position on the canvas
        void setChar(int x, int y, char ch);

        // Draw a line on the canvas from start to end with specified character
        void drawLine(int startX, int startY, int endX, int endY, char ch);

        void drawSquare(int x, int y, int width, int height, char ch, const std::string& buttonText = "", bool hollow = false);

        void drawCircle(int centerX, int centerY, int radius, char ch, bool hollow = false);

        void drawText(int x, int y, const std::string& text);

        void render() const;

        int getWidth() const;

        int getHeight() const;

        const char** getData() const;

    private:
        // Check if a given position is within the canvas bounds
        bool isValidPosition(const Vec2& pos) const;

    private:
        int width;          // Width of the canvas
        int height;         // Height of the canvas
        char** canvas;      // 2D array to represent the canvas
    };

}