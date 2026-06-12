#pragma once
#include<Section.h>
#include<QtWidgets/QRadioButton>
#include<memory>
#include<QtWidgets/QVBoxLayout>
using namespace std;
class FaceDirectionOfDrawSection:public Section{
public:
unique_ptr<QRadioButton> faceNormalButton=make_unique<QRadioButton>(tr("Face Normal Direction")); //face's normal direction
unique_ptr<QRadioButton> faceXButton=make_unique<QRadioButton>(tr("Face X Direction")); //face's x-direction
unique_ptr<QRadioButton> faceYButton=make_unique<QRadioButton>(tr("Face Y Direction")); //face's y direction
unique_ptr<QRadioButton> negFaceNormalButton=make_unique<QRadioButton>(tr("Negative Face Normal Direction"));
unique_ptr<QRadioButton> negFaceXButton=make_unique<QRadioButton>(tr("Negative Face X Direction"));
unique_ptr<QRadioButton> negFaceYButton=make_unique<QRadioButton>(tr("Negative Face Y Direction"));
unique_ptr<QVBoxLayout> vlayout;


public:
FaceDirectionOfDrawSection(QWidget* parent=nullptr):Section(tr("Face's Direction Of Draw")){
    vlayout=make_unique<QVBoxLayout>();
    vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    vlayout->addWidget(faceNormalButton.get());
    vlayout->addWidget(faceXButton.get());
    vlayout->addWidget(faceYButton.get());
    vlayout->addWidget(negFaceNormalButton.get());
    vlayout->addWidget(negFaceXButton.get());
    vlayout->addWidget(negFaceYButton.get());
    setContentLayout(*vlayout.get());
    return;
}
};


class FaceDirectionOfRotationSection:public Section{
public:
std::unique_ptr<QVBoxLayout> vlayout;
std::unique_ptr<QRadioButton> xRotate;
std::unique_ptr<QRadioButton> yRotate;
std::unique_ptr<QRadioButton> zRotate;



public:
FaceDirectionOfRotationSection(QWidget* parent=nullptr):Section(tr("Face's Direction Of Rotation")){
    vlayout=std::make_unique<QVBoxLayout>();
    vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    xRotate=std::make_unique<QRadioButton>(tr("Face X Direction"));
    yRotate=std::make_unique<QRadioButton>(tr("Face Y Direction"));
    zRotate=std::make_unique<QRadioButton>(tr("Face Normal Direction"));
    vlayout->addWidget(xRotate.get());
    vlayout->addWidget(yRotate.get());
    vlayout->addWidget(zRotate.get());
    setContentLayout(*vlayout.get());
}


};
