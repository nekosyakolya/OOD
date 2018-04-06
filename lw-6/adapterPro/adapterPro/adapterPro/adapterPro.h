#pragma once
#include "stdafx.h"

// Пространство имен графической библиотеки (недоступно для изменения)
namespace graphics_lib
{
// Холст для рисования
class ICanvas
{
public:
	// Ставит "перо" в точку x, y
	virtual void MoveTo(int x, int y) = 0;
	// Рисует линию с текущей позиции, передвигая перо в точку x,y
	virtual void LineTo(int x, int y) = 0;
	virtual void SetColor(uint32_t rgbColor) = 0;
	virtual ~ICanvas() = default;
};

// Реализация холста для рисования
class CCanvas : public ICanvas
{
public:
	void MoveTo(int x, int y) override
	{
		std::cout << "MoveTo (" << x << ", " << y << ")" << std::endl;
	}
	void LineTo(int x, int y) override
	{
		std::cout << "LineTo (" << x << ", " << y << ")" << std::endl;
	}
	void SetColor(uint32_t rgbColor) override
	{
		// TODO: вывести в output цвет в виде строки SetColor (#RRGGBB)
		std::cout << "color #" << std::hex << std::uppercase << rgbColor << std::dec << std::endl;
	}
};
} // namespace graphics_lib

// Пространство имен библиотеки для рисования фигур (использует graphics_lib)
// Код библиотеки недоступен для изменения
namespace shape_drawing_lib
{
struct Point
{
	int x;
	int y;
};

// Интерфейс объектов, которые могут быть нарисованы на холсте из graphics_lib
class ICanvasDrawable
{
public:
	virtual void Draw(graphics_lib::ICanvas& canvas) const = 0;
	virtual ~ICanvasDrawable() = default;
};

class CTriangle : public ICanvasDrawable
{
public:
	CTriangle(const Point& p1, const Point& p2, const Point& p3, uint32_t rgbColor = 0x000000)
		: m_point1(p1)
		, m_point2(p2)
		, m_point3(p3)
		, m_rgbColor(rgbColor)
	{
		// TODO: написать код конструктора
	}

	void Draw(graphics_lib::ICanvas& canvas) const override
	{
		// TODO: написать код рисования треугольника на холсте
		canvas.SetColor(m_rgbColor);
		canvas.MoveTo(m_point1.x, m_point1.y);

		canvas.LineTo(m_point2.x, m_point2.y);
		canvas.LineTo(m_point3.x, m_point3.y);
		canvas.LineTo(m_point1.x, m_point1.y);
	}

private:
	// TODO: дописать приватную часть
	Point m_point1;
	Point m_point2;
	Point m_point3;
	uint32_t m_rgbColor;
};

class CRectangle : public ICanvasDrawable
{
public:
	CRectangle(const Point& leftTop, int width, int height, uint32_t rgbColor = 0x000000)
		: m_leftTop(leftTop)
		, m_width(width)
		, m_height(height)
		, m_rgbColor(rgbColor)
	{
		// TODO: написать код конструктора
	}

	void Draw(graphics_lib::ICanvas& canvas) const override
	{
		// TODO: написать код рисования прямоугольника на холсте
		canvas.SetColor(m_rgbColor);
		canvas.MoveTo(m_leftTop.x, m_leftTop.y);

		canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
		canvas.LineTo(m_leftTop.x, m_leftTop.y);
	}

private:
	// TODO: дописать приватную часть
	Point m_leftTop;
	int m_width;
	int m_height;
	uint32_t m_rgbColor;
};

// Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
class CCanvasPainter
{
public:
	CCanvasPainter(graphics_lib::ICanvas& canvas)
		: m_canvas(canvas)
	{
		// TODO: дописать конструктор класса
	}
	void Draw(const ICanvasDrawable& drawable)
	{
		// TODO: дописать код рисования ICanvasDrawable на canvas, переданном в конструктор
		drawable.Draw(m_canvas);
	}

private:
	// TODO: дописать приватную часть
	graphics_lib::ICanvas& m_canvas;
};
} // namespace shape_drawing_lib

// Пространство имен современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib
{
class CPoint
{
public:
	CPoint(int x, int y)
		: x(x)
		, y(y)
	{
	}

	int x;
	int y;
};
// Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
class CRGBAColor
{
public:
	CRGBAColor(float r, float g, float b, float a)
		: r(r)
		, g(g)
		, b(b)
		, a(a)
	{
	}
	float r, g, b, a;
};

// Класс для современного рисования графики
class CModernGraphicsRenderer
{
public:
	CModernGraphicsRenderer(std::ostream& strm)
		: m_out(strm)
	{
	}

	~CModernGraphicsRenderer()
	{
		if (m_drawing) // Завершаем рисование, если оно было начато
		{
			EndDraw();
		}
	}

	// Этот метод должен быть вызван в начале рисования
	void BeginDraw()
	{
		if (m_drawing)
		{
			throw std::logic_error("Drawing has already begun");
		}
		m_out << "<draw>" << std::endl;
		m_drawing = true;
	}

	// Выполняет рисование линии
	void DrawLine(const CPoint& start, const CPoint& end, const CRGBAColor& color)
	{
		if (!m_drawing)
		{
			throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
		}
		m_out << boost::format(R"(<line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%">)") % start.x % start.y % end.x % end.y << std::endl;
		m_out << '\t' << boost::format(R"(<color r="%1%" g="%2%" b="%3%" a="%4%" />)") % color.r % color.g % color.b % color.a << std::endl;
		m_out << "</line>" << std::endl;
	}

	// Этот метод должен быть вызван в конце рисования
	void EndDraw()
	{
		if (!m_drawing)
		{
			throw std::logic_error("Drawing has not been started");
		}
		m_out << "</draw>" << std::endl;
		m_drawing = false;
	}

private:
	std::ostream& m_out;
	bool m_drawing = false;
};
} // namespace modern_graphics_lib

// Пространство имен приложения (доступно для модификации)
namespace app
{
class CModernGraphicsRendererAdapter : public graphics_lib::ICanvas
{
public:
	CModernGraphicsRendererAdapter(modern_graphics_lib::CModernGraphicsRenderer& render)
		: m_render(render)
		, m_currentPoint(modern_graphics_lib::CPoint(0, 0))
		, m_rgbaColor(modern_graphics_lib::CRGBAColor(0, 0, 0, 1.0))
	{
		m_render.BeginDraw();
	}

	void MoveTo(int x, int y) override
	{
		m_currentPoint = modern_graphics_lib::CPoint(x, y);
	}

	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint endPoint(x, y);
		m_render.DrawLine(m_currentPoint, endPoint, m_rgbaColor);

		m_currentPoint = endPoint;
	}
	void SetColor(uint32_t rgbColor) override
	{
		m_rgbaColor.r = ((rgbColor >> 16) & 0xff) / 255.f;
		m_rgbaColor.g = ((rgbColor >> 8) & 0xff) / 255.f;
		m_rgbaColor.b = (rgbColor & 0xff) / 255.f;
	}

private:
	modern_graphics_lib::CRGBAColor m_rgbaColor;
	modern_graphics_lib::CPoint m_currentPoint;
	modern_graphics_lib::CModernGraphicsRenderer& m_render;
};

inline void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
{
	using namespace shape_drawing_lib;

	CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0x012345);
	CRectangle rectangle({ 30, 40 }, 18, 24, 0x520057);

	// TODO: нарисовать прямоугольник и треугольник при помощи painter

	painter.Draw(rectangle);
	painter.Draw(triangle);
}

inline void PaintPictureOnCanvas()
{
	graphics_lib::CCanvas simpleCanvas;
	shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

inline void PaintPictureOnModernGraphicsRenderer()
{
	modern_graphics_lib::CModernGraphicsRenderer renderer(std::cout);
	// TODO: при помощи существующей функции PaintPicture() нарисовать
	// картину на renderer
	// Подсказка: используйте паттерн "Адаптер"
	CModernGraphicsRendererAdapter adapter(renderer);

	shape_drawing_lib::CCanvasPainter painter(adapter);
	PaintPicture(painter);
}
} // namespace app
