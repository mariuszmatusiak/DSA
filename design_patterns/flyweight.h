#ifndef DSA_ADAPTER_H
#define DSA_ADAPTER_H

class Texture {

};

class NaiveTree {

};

class Tree {
public:
    Tree(const Texture* t) : texture(t) {}
    void setPos (double _x, double _y, double _w, double _h) {
        x = _x;
        y = _y;
        width = _w;
        height = _h;
    }
private:
    // intrinsic state:
    Texture* texture;
    // extrinsic state:
    double x;
    double y;
    double width;
    double height;
};

class TreeRenderer {
public:
    Tree* makeTree(const string& filename) {
        if (auto it = treePool.find(filename) != treePool.end())
        {
            return it->second;
        }
    }
private:
    unordered_map<string, Tree*> treePool;
    unordered_map<string, Texture*> texturePool;
};

#endif /* DSA_ADAPTER_H */
