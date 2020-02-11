#pragma once
#include <iostream>
#include <string>
#include <cctype>


class ln80c_buffer : public std::streambuf {
private:
    std::streambuf* buffer;
    size_t N; //string number
    size_t lenght; //current length
    bool newString; //

public:
    // default constructor
    ln80c_buffer(std::streambuf* buff):
            buffer(buff)
            , N(0)
            , lenght(0)
            , newString(true)
            {}

protected:
    // overflow override
    int_type overflow(int_type c = EOF) override {
        if (newString) {
            std::string str = std::to_string(++N);
            if(str.length() < 8)
                str = std::string(8 - str.length(), ' ') + str;
            buffer->sputn(str.c_str(), 8);

            newString = false;
            lenght = 0;
        }
        if ((char)c == '\n') {
            newString = true;
            buffer->sputc(c);
        }
        else if (lenght == 71) {
            newString = true;

            buffer->sputc((char)c);
            buffer->sputc('\n');
        } else
            buffer->sputc((char)c);
        ++lenght;
        return c;
    }
};


class stat_buffer: public std::streambuf {
private:
    std::streambuf* buffer;
    size_t lineCount;
    size_t wordCount;
    size_t charCount;
    bool prevCharIsAlpha;
    int c;
public:
    stat_buffer(std::streambuf* buf):
    buffer(buf)
    , lineCount(0)
    , wordCount(0)
    , charCount(0)
    , prevCharIsAlpha(false)
    {}

    int getLineCount() {
        return lineCount;
    }

    int getWordCount() {
        return wordCount;
    }

    int getCharCount() {
        return charCount;
    }
    int_type underflow() override {
        while ((c = buffer->sbumpc()) != EOF) {
            if (std::isalpha(c)) {
                if (!prevCharIsAlpha) {
                    wordCount++;
                    prevCharIsAlpha = true;
                }
            } else
                prevCharIsAlpha = false;

            if (c == '\n') {
                lineCount++;
//                std::cout << '\n' << "current number of words = " << getWordCount() << '\n';
//                std::cout << "current number of characters(include '\\n') = " << getCharCount() + 1 << '\n';
//                std::cout << "current number of lines = " << getLineCount() + 1 << '\n';
            }

            charCount++;

            char ch(c);
            setg(&ch, &ch, &ch + 1);
            return c;
        }
        return c;
    }

};

