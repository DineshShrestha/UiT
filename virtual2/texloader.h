#ifndef TEXLOADER_H
#define TEXLOADER_H

#include <vector>
#include <gmParametricsModule>

// qt
#include <QImage>
#include <QOpenGLTexture>
#include <QImageReader>
#include <QDirIterator>

namespace GMlib {
template <typename T, int n>
class  PSurfTexVisualizer;
}

namespace ALLlib {


class TexLoader {

public:
    GMlib::PSurfTexVisualizer<float, 3>* loadTexture(QString fileName) const;

};
}
#endif // TEXLOADER_H
