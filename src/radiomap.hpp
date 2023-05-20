#ifndef RADIOMAP_H
#define RADIOMAP_H

#include <dataloader.hpp>

class District {
    private:
        Data *samples;
    public:
        void read_file(int district_num);
};

class RadioMap {
    private:
        District **districts;
    public:
        void read_file();
};

#endif /* RADIOMAP_H */