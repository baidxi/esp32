#pragma once

class application {
public:
    application(const application&) = delete;
    application operator=(const application&) = delete;

    static application& get_instance() {
        static application instance;
        return instance;
    }

    void start();

private:
    application();
    ~application();
};