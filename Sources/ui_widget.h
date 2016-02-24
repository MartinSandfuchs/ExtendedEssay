/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
 public:
	QWidget *layoutWidget;
	QHBoxLayout *horizontalLayout;
	QSlider *horizontalSlider;
	QLabel *label;
	QPushButton *pushButton;

	void setupUi(QWidget *Widget) {
		if (Widget->objectName().isEmpty())
			Widget->setObjectName(QStringLiteral("Widget"));
		Widget->resize(800, 800);
		layoutWidget = new QWidget(Widget);
		layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
		layoutWidget->setGeometry(QRect(10, 10, 371, 26));
		horizontalLayout = new QHBoxLayout(layoutWidget);
		horizontalLayout->setSpacing(6);
		horizontalLayout->setContentsMargins(11, 11, 11, 11);
		horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
		horizontalLayout->setContentsMargins(0, 0, 0, 0);
		horizontalSlider = new QSlider(layoutWidget);
		horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
		horizontalSlider->setMinimum(30);
		horizontalSlider->setMaximum(120);
		horizontalSlider->setValue(60);
		horizontalSlider->setOrientation(Qt::Horizontal);

		horizontalLayout->addWidget(horizontalSlider);

		label = new QLabel(layoutWidget);
		label->setObjectName(QStringLiteral("label"));
		QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
		sizePolicy.setHorizontalStretch(0);
		sizePolicy.setVerticalStretch(0);
		sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
		label->setSizePolicy(sizePolicy);
		QFont font;
		font.setFamily(QStringLiteral("SignPainter"));
		font.setPointSize(12);
		label->setFont(font);

		horizontalLayout->addWidget(label);

		pushButton = new QPushButton(layoutWidget);
		pushButton->setObjectName(QStringLiteral("pushButton"));
		QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
		sizePolicy1.setHorizontalStretch(0);
		sizePolicy1.setVerticalStretch(0);
		sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
		pushButton->setSizePolicy(sizePolicy1);

		horizontalLayout->addWidget(pushButton);


		retranslateUi(Widget);

		QMetaObject::connectSlotsByName(Widget);
	} // setupUi

	void retranslateUi(QWidget *Widget) {
		Widget->setWindowTitle(QApplication::translate("Widget", "3D View", 0));
		label->setText(QApplication::translate("Widget", "60", 0));
		pushButton->setText(QApplication::translate("Widget", "Save Image", 0));
	} // retranslateUi

};

namespace Ui {
	class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
