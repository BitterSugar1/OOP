#pragma once

class IPrintable {
public:
    virtual void printStatus() const = 0;
    virtual ~IPrintable() = default;
};
