#ifndef DATALOADER_H
#define DATALOADER_H

class Rss {
    public:
        char *bssid;
        float *rss;
};

class Data {
    public:
        Rss *rss_array;
        void read_test_file(int testset_num);
};

#endif /* DATALOADER_H */