#include "toolbutton.h"

ToolButton::ToolButton(QToolButton *parent) :
    QToolButton(parent)
{
    connect(this,SIGNAL(clicked()),this,SLOT(slotDelframe()));
}

void ToolButton::enterEvent(QEvent *)
{
    emit sigChangeStatus(this->accessibleDescription());
}

void ToolButton::leaveEvent(QEvent *)
{
    emit sigChangeStatus("");
}

void ToolButton::slotDelframe()
{
    this->setFocusPolicy(Qt::NoFocus);
    this->setAutoRaise(true);
}
