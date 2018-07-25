#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>


#define PB_EXTRA_SPACE 3
#define PB_RADIUS 7
#define PB_BAR_WIDTH_FACTOR 0.1
#define PB_BAR_X_INCREMENT 0.1


class ProgressBar : public QWidget
{
Q_OBJECT
public:
    explicit ProgressBar(QWidget *parent = 0);

public slots:

    void SetBackgroundColor(const QColor& clr);

    void SetRange(int min,int max);

    void SetValue(int value);

    void StartSuspending();

    void StopSuspending();

protected:
    void paintEvent(QPaintEvent *);

    QSize sizeHint() const
    {
        return QSize(200,30);
    }

private:

    void drawBackground(QPainter* painter);

    void drawBar(QPainter* painter);

private:

    QColor m_bgClr;

    int m_nMin;
    int m_nMax;
    int m_nValue;
    int m_nCurrentValue;

    qreal m_BarLength;

    bool m_bReverse;
    bool m_bSuspending;
    bool m_bBarReverse;

    int m_nCurrentXPos;

    QTimer* m_updateTimer;
    QTimer* m_suspendingTimer;

private:
    void initVariables();

private slots:
    void UpdateData();
    void DoSuspending();

};

#endif // PROGRESSBAR_H
