#include "StdAfx.h"
#include ".\acdbpolyline.h"

CAcDbPolyLine::CAcDbPolyLine(void) {
    m_PenSize = 1.0f;
    m_HasFoundColor = false;
    m_Color = -1;
}

CAcDbPolyLine::~CAcDbPolyLine(void) {
}

void CAcDbPolyLine::AddPoint(const double &param_dXVal, const double &param_dYVal, const double &param_dBulge) {
    m_pointVertex.push_back(CDxfPoint(param_dXVal, param_dYVal, param_dBulge));
}

void CAcDbPolyLine::SetLayer(const string &param_strLayer) {
    m_strLayer = param_strLayer;
    MakeValid();
}

void CAcDbPolyLine::SetPenSize(double PSize) {
    m_PenSize = PSize;
}

void CAcDbPolyLine::SetFlag(int pFlag) {
    m_Flag = pFlag;
}
int CAcDbPolyLine::GetFlag(void) {
    return m_Flag;
}

double CAcDbPolyLine::GetPenSize(void) {
    return m_PenSize;
}

const string& CAcDbPolyLine::GetLayerName(void) const {
    return m_strLayer;
}

int CAcDbPolyLine::GetVertexCount(void) const {
    return static_cast<int>(m_pointVertex.size());
}

CDxfPoint CAcDbPolyLine::GetMinBound(void) const {
    double x = m_pointVertex[0].GetX();
    double y = m_pointVertex[0].GetY();

    for (int i = 1; i < GetVertexCount(); i++) {
        x = min(x, m_pointVertex[i].GetX());
        y = min(y, m_pointVertex[i].GetY());
    } // for(int i=1; i<GetVertexCount(); i++)

    return CDxfPoint(x, y);
}

CDxfPoint CAcDbPolyLine::GetMaxBound(void) const {
    double x = m_pointVertex[0].GetX();
    double y = m_pointVertex[0].GetY();

    for (int i = 1; i < GetVertexCount(); i++) {
        x = max(x, m_pointVertex[i].GetX());
        y = max(y, m_pointVertex[i].GetY());
    } // for(int i=1; i<GetVertexCount(); i++)

    return CDxfPoint(x, y);
}
const CDxfPoint& CAcDbPolyLine::operator[](const int &param_iIndex) const {
    return m_pointVertex[param_iIndex];
}

int CAcDbPolyLine::GetColor(bool *HasColor) const {
    if (HasColor) {
        *HasColor = m_HasFoundColor;

    }
    return m_Color;
}

void CAcDbPolyLine::SetColor(int p_Color) {
    m_HasFoundColor = true;
    m_Color = p_Color;
}

