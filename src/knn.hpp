#ifndef KNN_H
#define KNN_H

class KNN {
    private:
        RadioMap radiomap;
        Data test;

    public:
        KNN (RadioMap radiomap, Data testset);
        int run();
        float calculate_distance_squared();
};

#endif /* KNN_H */