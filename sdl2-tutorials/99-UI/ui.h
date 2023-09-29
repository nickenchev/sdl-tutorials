#pragma once

#include <vector>
#include <variant>
#include <string>

namespace UI
{
	struct Rect
	{
		float x, y, width, height;

		Rect() : x(0), y(0), width(0), height(0) { }
		Rect(float x, float y, float width, float height)
		{
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
		}
	};

	/*
	class Widget
	{
		std::vector<Widget *> children;

	public:
		Rect rect;

		Widget()
		{
		}

		void addChild(Widget *child)
		{
			children.push_back(child);
		}

		auto &getChildren()
		{
			return children;
		}

		virtual void layout(const Rect &parentRect)
		{
			for (Widget *widget : getChildren())
			{
				widget->layout(parentRect);
			}
		}
	};

	class Spacer : public Widget
	{
	};

	class Panel : public Widget
	{
	public:
		unsigned int colors[3] = { 0, 0, 0 };
	};

	enum class LayoutDirection
	{
		horizontal,
		vertical
	};

	class Layout : public Widget
	{
		LayoutDirection direction;

	public:
		Layout(LayoutDirection direction)
		{
			this->direction = direction;
		}

		void layout(const Rect &parentRect) override
		{
			if (direction == LayoutDirection::horizontal)
			{
				unsigned int availableWidth = parentRect.width;
				int i = 0;
				for (auto *widget : getChildren())
				{
					int childWidth = parentRect.width / static_cast<int>(getChildren().size());
					widget->rect.x = childWidth * i;
					widget->rect.y = 0;
					widget->rect.width = childWidth;
					widget->rect.height = parentRect.height;
					widget->layout(widget->rect);
					++i;
				}
			}
			else
			{
				unsigned int availableHeight = parentRect.height;
				int i = 0;
				for (auto *widget : getChildren())
				{
					int childHeight = parentRect.height / static_cast<int>(getChildren().size());
					widget->rect.x = parentRect.x;
					widget->rect.y = childHeight * i;
					widget->rect.width = parentRect.width;
					widget->rect.height = childHeight;
					widget->layout(widget->rect);
					++i;
				}
			}
		}
	};
	*/

	class HorizontalLayout {};
	class VerticalLayout {};

	class Panel {};
	class Spacer {};
	class Label
	{
		std::string text;
	public:
		Label(const std::string &text) : text(text) {}
	};

	using Layout = std::variant<HorizontalLayout, VerticalLayout>;
	using Control = std::variant<Spacer, Panel, Label>;

	class Widget
	{
		Rect rect;
		Layout layout;
		Control control;
		std::vector<Widget> children;

	public:
		Widget(Control control)
		{
			this->layout = VerticalLayout();
			this->control = control;
		}

		Widget &addChild(Widget &&widget)
		{
			children.push_back(widget);
			return children[children.size() - 1];
		}

		Rect getRect() const { return rect; }
		void setRect(const Rect &rect)
		{
			this->rect = rect;
		}


		void setLayout(Layout layout) { this->layout = layout; }
		Layout getLayout() { return layout; }
		Control getControl() { return control; }
		auto &getChildren() { return children; }
	};

	struct LayoutVisitor
	{
		void layout(Widget &widget)
		{
			switch (widget.getLayout().index())
			{
				case 0:
				{
					auto layout = std::get<0>(widget.getLayout());
					(*this)(layout, widget);
					break;
				}
				case 1:
				{
					auto layout = std::get<1>(widget.getLayout());
					(*this)(layout, widget);
					break;
				}
				default:
				{
					break;
				}
			}

			for (Widget &childWidget : widget.getChildren())
			{
				layout(childWidget);
			}
		}
		void operator()(HorizontalLayout &layout, Widget &widget)
		{
			const Rect parentRect = widget.getRect();
			int i = 0;

			for (auto &childWidget : widget.getChildren())
			{
				float childWidth = parentRect.width / static_cast<int>(widget.getChildren().size());
				Rect childRect{ childWidth * i, 0, childWidth, parentRect.height };
				childWidget.setRect(childRect);
				++i;
			}
		}

		void operator()(VerticalLayout &layout, Widget &widget)
		{
			const Rect parentRect = widget.getRect();
			int i = 0;

			for (auto &childWidget : widget.getChildren())
			{
				float childHeight = parentRect.height / static_cast<int>(widget.getChildren().size());
				Rect childRect{ parentRect.x, childHeight * i, parentRect.width, childHeight };
				childWidget.setRect(childRect);
				++i;
			}
		}
	};


}
