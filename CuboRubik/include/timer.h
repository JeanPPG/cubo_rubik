// timer.h

#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <sstream>
#include <iomanip>

class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock> startTime; // Almacena el momento en que comienza el temporizador
    bool running; // Indica si el temporizador está en marcha o no

public:
    Timer() : running(false) {} // Constructor que inicializa el temporizador como no en marcha

    // Inicia el temporizador
    void start() {
        startTime = std::chrono::steady_clock::now(); // Registra el momento actual
        running = true; // Establece el indicador de en marcha como verdadero
    }

    // Detiene el temporizador
    void stop() {
        running = false; // Establece el indicador de en marcha como falso
    }

    // Calcula y devuelve el tiempo transcurrido como una cadena en el formato HH:MM:SS
    std::string elapsed_time() {
        if (!running) return "00:00:00"; // Si el temporizador no está en marcha, devuelve 00:00:00

        auto currentTime = std::chrono::steady_clock::now(); // Obtiene el momento actual
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count(); // Calcula el tiempo transcurrido en segundos

        // Convierte el tiempo transcurrido a horas, minutos y segundos
        int hours = elapsedTime / 3600;
        int minutes = (elapsedTime % 3600) / 60;
        int seconds = elapsedTime % 60;

        // Formatea el tiempo transcurrido como HH:MM:SS y lo devuelve como una cadena
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2) << minutes << ":" << std::setw(2) << seconds;
        return ss.str();
    }
};

#endif // TIMER_H
