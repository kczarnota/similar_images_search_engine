#ifndef BAGOFWORDS_SHOWIMAGES_HPP
#define BAGOFWORDS_SHOWIMAGES_HPP
#include <QThread>
#include "src/Model/BOW.hpp"


class ShowImages : public QThread
{
    Q_OBJECT

public:
    ShowImages() {};
    ShowImages(BOW * b);
    void showManyImages(char* title, int nArgs, IplImage ** images);

protected:
    void run();

private:
    BOW * bow;

};


#endif //BAGOFWORDS_SHOWIMAGES_HPP
