#ifndef DSA_ADAPTER_H
#define DSA_ADAPTER_H

class IAudioStreamer {
public:
    virtual void playSong() = 0;
};

class SpotifyStreamer : public IAudioStreamer {
public:
    void playSong() override {
        // 1. Download
        // 2. Decode
        // 3. Play
    }
};

class ProxySpotifyStreamer : public IAudioStreamer {
public:
    explicit ProxySpotifyStreamer() : spotifyStreamer(nullptr)
    void playSong() override {
        if (spotifyStreamer == nullptr) {
            spotifyStreamer = make_unique<SpotifyStreamer>();
        }
        spotifyStreamer->playSong();
    }

private:
    unique_ptr<SpotifyStreamer> spotifyStreamer;
};

#endif /* DSA_ADAPTER_H */
