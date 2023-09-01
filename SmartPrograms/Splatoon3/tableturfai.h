#ifndef TABLETURFAI_H
#define TABLETURFAI_H

#include <QDebug>
#include <QObject>
#include <QImage>

#include "../smartprogrambase.h"

class TableTurfAI : public QObject
{
    Q_OBJECT
public:
    TableTurfAI();

    void Restart();
    void UpdateFrame(QImage const& image);

private:
    enum GridType : uint8_t
    {
        GT_Empty,
        GT_InkOrange,
        GT_InkOrangeSp,
        GT_InkBlue,
        GT_InkBlueSp,
        GT_Neutral
    };

    #define CARD_SIZE 8
    #define CARD_TILE_SIZE 14
    struct Card
    {
        Card() { Reset(); }

        void Reset();
        void Rotate(bool clockwise);

        bool m_init;
        bool m_usable;
        QPoint m_center;
        int m_tileCount;
        GridType m_tile[CARD_SIZE][CARD_SIZE];
    };

private:
    void AnalysisBoard();
    bool UpdateBoardTile(QRect rect, GridType& tileType);

    void AnalysisHands();
    bool UpdateCardTile(QRect rect, GridType& tileType);

    void ExportBoard();
    void ExportCards();

    qreal GetColorPixelRadio(QRect rect, HSVRange hsvRange);

private:
    QImage m_frame;

    #define BOARD_SIZE_X 9
    #define BOARD_SIZE_Y 26
    #define BOARD_TILE_SIZE 25
    GridType m_board[BOARD_SIZE_X][BOARD_SIZE_Y];
    Card m_cards[4];
    int m_spCount;

    HSVRange const c_hsvEmpty = HSVRange(0,0,0,359,255,40);
    HSVRange const c_hsvNeutral = HSVRange(0,0,160,359,50,200);
    HSVRange const c_hsvInkOrange = HSVRange(50,100,220,90,255,255);
    HSVRange const c_hsvInkOrangeSp = HSVRange(10,100,220,50,255,255);
    HSVRange const c_hsvInkBlue = HSVRange(220,100,220,260,255,255);
    HSVRange const c_hsvInkBlueSp = HSVRange(160,100,220,200,255,255);
    HSVRange const c_hsvInkBlueSpFire = HSVRange(160,0,220,200,100,255);

    QVector<QColor> const c_debugColors =
    {
        QColor(0,0,0),
        QColor(255,255,0),
        QColor(255,128,64),
        QColor(0,128,255),
        QColor(0,255,255),
        QColor(128,128,128)
    };

    qreal const c_colorPixelRatio = 120;
    QPointF const c_boardTopLefts[BOARD_SIZE_Y]
    {
        QPointF(650,8),
        QPointF(650,35),
        QPointF(650,60),
        QPointF(650,87),
        QPointF(650,113),
        QPointF(650,138),
        QPointF(650,164),
        QPointF(650,190),
        QPointF(650,217),
        QPointF(650,244),
        QPointF(650,270),
        QPointF(650,296),
        QPointF(650,323),
        QPointF(650,349),
        QPointF(650,376),
        QPointF(650,404),
        QPointF(650,430),
        QPointF(650,456),
        QPointF(650,483),
        QPointF(650,510),
        QPointF(650,538),
        QPointF(650,565),
        QPointF(650,592),
        QPointF(650,619),
        QPointF(650,647),
        QPointF(650,674)
    };
    qreal const c_boardXSeparations[BOARD_SIZE_Y] =
    {
        26.25,
        26.25,
        26.375,
        26.375,
        26.375,
        26.375,
        26.375,
        26.5,
        26.5,
        26.5,
        26.5,
        26.625,
        26.625,
        26.625,
        26.625,
        26.75,
        26.75,
        26.75,
        26.75,
        26.75,
        26.875,
        26.875,
        26.875,
        26.875,
        27,
        27
    };

    QPointF const c_handTopLefts[4] =
    {
        QPointF(24,123),
        QPointF(201,132),
        QPointF(32,341),
        QPointF(202,342)
    };
    QPointF const c_handSteps[4] =
    {
        QPointF(17.875,16.75),
        QPointF(16,15.375),
        QPointF(17,15.875),
        QPointF(15.875,15.25)
    };
    QPointF const c_handOffsets[4] =
    {
        QPointF(0.625,0.125),
        QPointF(0,0.75),
        QPointF(0,0.125),
        QPointF(0,0),
    };

    HSVRange const c_hsvCardInk = HSVRange(60,170,100,70,255,255);
    HSVRange const c_hsvCardInkSp = HSVRange(45,170,100,55,255,255);
    HSVRange const c_hsvCardDark = HSVRange(60,170,100,70,255,180);
};

#endif // TABLETURFAI_H