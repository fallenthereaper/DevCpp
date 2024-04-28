#pragma once

#include "src/core/text_canvas.h"
namespace GameRenderer {

    TextCanvas::TextCanvas(int width, int height) : width(width), height(height) {
        // Allocate memory for the canvas
         // Allocate memory for the canvas
        canvas = new char* [height];
        for (int i = 0; i < height; ++i) {
            canvas[i] = new char[width];
            // Initialize canvas with spaces
            std::fill(canvas[i], canvas[i] + width, ' ');
        }
    }

    const char** TextCanvas::getData() const {
        return const_cast<const char**>(canvas);
    }

    int TextCanvas::getWidth() const {
        return width;
    };

    int TextCanvas::getHeight() const {
        return height;
    };

    TextCanvas::~TextCanvas() {
        // Deallocate memory for the canvas
        for (int i = 0; i < height; ++i) {
            delete[] canvas[i];
        }
        delete[] canvas;

        // Clear the state stack
        while (!stateStack.empty()) {
            char** state = stateStack.top();
            stateStack.pop();
            for (int i = 0; i < height; ++i) {
                delete[] state[i];
            }
            delete[] state;
        }
    }

    void TextCanvas::clear() {
        // Reset canvas by filling with spaces
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                canvas[i][j] = ' ';
            }
        }
    }


    void TextCanvas::push() {
        char** currentState = new char* [height];
        for (int i = 0; i < height; ++i) {
            currentState[i] = new char[width];
            std::copy(canvas[i], canvas[i] + width, currentState[i]);
        }
        stateStack.push(currentState);
    }
    void TextCanvas::copyCanvas(char** dest, char** src) const {
        std::copy(src, src + width, dest);
    }
    void TextCanvas::pop() {
        if (!stateStack.empty()) {
            char** prevState = stateStack.top();
            stateStack.pop();

            // Restore the previous state
            for (int i = 0; i < height; ++i) {
                std::copy(prevState[i], prevState[i] + width, canvas[i]);
                delete[] prevState[i];
            }
            delete[] prevState;
        }
    }


    void TextCanvas::setChar(const Vec2& pos, char ch) {
        if (isValidPosition(pos)) {
            canvas[(int) pos.y][(int)pos.x] = ch;
        }
    }

    void TextCanvas::drawLine(const Vec2& start, const Vec2& end, char ch) {
        Vec2 delta = end - start;
        int steps = std::max(std::abs(delta.x), std::abs(delta.y));

        for (int i = 0; i <= steps; ++i) {
            Vec2 point = start + Vec2(delta.x * i / steps, delta.y * i / steps);
            setChar(point, ch);
        }
    }

    void TextCanvas::drawCircle(const Vec2& center, int radius, char ch, bool hollow ) {
        for (int y = -radius; y <= radius; ++y) {
            for (int x = -radius; x <= radius; ++x) {
                if (x * x + y * y <= radius * radius) {
                    Vec2 point = center + Vec2(x, y);
                    if (!hollow || (std::abs(x) == radius || std::abs(y) == radius)) {
                        setChar(point, ch);
                    }
                }
            }
        }
    }

    void TextCanvas::drawSquare(const Vec2& topLeft, int width, int height, char ch, const std::string& buttonText, bool hollow) {
        if (!hollow) {
            for (int y = topLeft.y; y < topLeft.y + height; ++y) {  //FULL SQUARE
                for (int x = topLeft.x; x < topLeft.x + width; ++x) {
                    setChar(Vec2(x, y), ch);
                }
            }
        }
        else {
            drawLine(topLeft, Vec2(topLeft.x + width - 1, topLeft.y), ch); // Top side
            drawLine(topLeft, Vec2(topLeft.x, topLeft.y + height - 1), ch); // Left side
            drawLine(Vec2(topLeft.x + width - 1, topLeft.y), Vec2(topLeft.x + width - 1, topLeft.y + height - 1), ch); // Right side
            drawLine(Vec2(topLeft.x, topLeft.y + height - 1), Vec2(topLeft.x + width - 1, topLeft.y + height - 1), ch); // Bottom side
        }

        if (!buttonText.empty()) {
            int textPosX = ((int)topLeft.x) + (width - buttonText.length()) / 2;
            int textPosY = ((int)topLeft.y) + height / 2;

            drawText(Vec2(textPosX, textPosY), buttonText);
        }
    }

    void TextCanvas::drawText(const Vec2& pos, const std::string& text) {
        for (size_t i = 0; i < text.length(); ++i) {
            setChar(Vec2(pos.x + i, pos.y), text[i]);
        }
    }

    bool TextCanvas::isValidPosition(const Vec2& pos) const {
        return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height;
    }

    void TextCanvas::render() const {
      
        // Render canvas content
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::cout << canvas[i][j];
            }
            std::cout << std::endl;
        }
    }

}