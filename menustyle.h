/*
  @file
  @author Stefan Frings
*/
#ifndef MENUSTYLE_H
#define MENUSTYLE_H

#include <QProxyStyle>
#include <QStyleOption>
/*
 * This proxy style changes the size of icons relative to the font size.
 * I use it to give icons a proper size on high-res displays.
 */
class MenuStyle : public QProxyStyle
{
public:
	/* Calculate the size of icons relative to the font size */
	int pixelMetric(PixelMetric metric, const QStyleOption *option=0, const QWidget *widget=0) const;
};

#endif // MENUSTYLE_H
