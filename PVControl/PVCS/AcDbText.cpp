#include "StdAfx.h"
#include ".\acdbtext.h"

CAcDbText::CAcDbText(void)
    : m_dHeight(0.0)
    , m_dWidth(0.0)
    , m_iDrawDir(0)
    , m_iLSpace(0)
    , m_iAttachPnt(5)
    , m_xAngle(0.0)
    , m_yAngle(0.0)
    , m_zAngle(0.0) {
    m_strFont = L"Tahoma";
}

CAcDbText::~CAcDbText(void) {
}

void CAcDbText::SetX(const double &param_dXVal) {
    m_pointPosition.SetX(param_dXVal);
}

void CAcDbText::SetY(const double &param_dYVal) {
    m_pointPosition.SetY(param_dYVal);
}

void CAcDbText::SetValue(const string &param_strValue) {
    m_strValue = param_strValue;
    MakeValid();
}

void CAcDbText::SetLayer(const string &param_strLayer) {
    m_strLayer = param_strLayer;
}

void CAcDbText::SetFont(const string &param_strFont) {
    m_strFont = L"";
    for (unsigned i = 0; i < param_strFont.size(); i++) {
        m_strFont += param_strFont[i];
    }
    if (m_strFont.size() < 5) {
        m_strFont = L"Tahoma";
    }
}

void CAcDbText::SetHeight(const double &param_dHeight) {
    m_dHeight = param_dHeight;
}

void CAcDbText::SetDrawDir(const int &param_iDrawDir) {
    m_iDrawDir = param_iDrawDir;
}

void CAcDbText::SetLSpace(const int &param_iLSpace) {
    m_iLSpace = param_iLSpace;
}

void CAcDbText::SetAttachPnt(const int &param_iAttachPnt) {
    m_iAttachPnt = param_iAttachPnt;
}

const CDxfPoint& CAcDbText::GetPosition(void) const {
    switch (m_iAttachPnt) {
    case 1: // Top left
        break;
    case 2: // Top center
        break;
    case 3: // Top right
        break;
    case 4: // Middle left
        break;
    case 5: // Middle center
        break;
    case 6: // Middle right
        break;
    case 7: // Bottom left
        break;
    case 8: // Bottom center
        break;
    case 9: // Bottom right
        break;
    }
    return m_pointPosition;
}

const string& CAcDbText::GetValue(void) const {
    return m_strValue;
}

const string& CAcDbText::GetLayer(void) const {
    return m_strLayer;
}

const wstring& CAcDbText::GetFont(void) const {
    return m_strFont;
}

const double& CAcDbText::GetHeight(void) {
    return m_dHeight;
}

void CAcDbText::SetWidth(const double &param_dWidth) {
    m_dWidth = param_dWidth;
}

const double& CAcDbText::GetWidth(void) const {
    return m_dWidth;
}


void CAcDbText::SetXAngle(const double &param_dAngle) {
    m_xAngle = param_dAngle;
}
void CAcDbText::SetYAngle(const double &param_dAngle) {
    m_yAngle = param_dAngle;
}
void CAcDbText::SetZAngle(const double &param_dAngle) {
    m_zAngle = param_dAngle;
}

const double& CAcDbText::GetXAngle(void) const {
    return m_xAngle;
}
const double& CAcDbText::GetYAngle(void) const {
    return m_yAngle;
}
const double& CAcDbText::GetZAngle(void) const {
    return m_zAngle;
}

const int& CAcDbText::GetAttachPnt(void) const {
    return m_iAttachPnt;
}

