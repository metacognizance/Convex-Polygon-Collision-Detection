#include "Application.hpp"

Application::Application(int argc, char** argv)
{
	run();
}

Application::~Application()
{

}

void Application::initialize()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 32;

	m_window.create(sf::VideoMode(1600, 900), "Convex-Polygon-Collision-Detection", sf::Style::Close, settings);
	
	a.addPoint(sf::Vector2f(0, 0));
	a.addPoint(sf::Vector2f(25, -10));
	a.addPoint(sf::Vector2f(50, 0));
	a.addPoint(sf::Vector2f(60, 25));
	a.addPoint(sf::Vector2f(50, 50));
	a.addPoint(sf::Vector2f(0, 50));
	a.offset(100, 100);
	a.constructEdges();

	_a.setPointCount(a.getPointCount());
	for (int i = 0; i < a.getPointCount(); ++i)
		_a.setPoint(i, a.getPoint(i));
	_a.setOutlineColor(sf::Color::Red);

	b.addPoint(sf::Vector2f(0, 0));
	b.addPoint(sf::Vector2f(500, 0));
	b.addPoint(sf::Vector2f(550, 75));
	b.addPoint(sf::Vector2f(275, 100));
	b.addPoint(sf::Vector2f(10, 45));
	b.offset(150, 100);
	b.constructEdges();

	_b.setPointCount(b.getPointCount());
	for (int i = 0; i < b.getPointCount(); ++i)
		_b.setPoint(i, b.getPoint(i));
	_b.setOutlineColor(sf::Color::Red);
	
	c.addPoint(sf::Vector2f(-50, 0));
	c.addPoint(sf::Vector2f(60, 5));
	c.addPoint(sf::Vector2f(500, 500));
	c.addPoint(sf::Vector2f(400, 500));
	c.addPoint(sf::Vector2f(100, 250));
	c.offset(700, 100);
	c.constructEdges();

	_c.setPointCount(c.getPointCount());
	for (int i = 0; i < c.getPointCount(); ++i)
		_c.setPoint(i, c.getPoint(i));
	_c.setOutlineColor(sf::Color::Red);

	m_running = true;
	m_active = true;
	m_space = false;
	m_mouse = false;
}

void Application::run()
{
	initialize();
	
	sf::Clock dt;
	sf::Time deltaTime;
	sf::Time updateTime = sf::seconds(1.f/60.f);

	while(m_running)
	{
		deltaTime += dt.getElapsedTime();
		dt.restart();

		handleEvents();
		render();
		while (deltaTime >= updateTime && m_active)
		{
			update(deltaTime);
			deltaTime -= updateTime;
		}
	}
}

void Application::handleEvents()
{
	sf::Event event;

	while(m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}
	}
}

void Application::update(sf::Time & p_deltaTime)
{
	sf::Vector2f velocity = sf::Vector2f(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y = -5;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.y = 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x = -5;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x = 5;
	}

	if (velocity != sf::Vector2f(0, 0))
	{
		auto intersect = math::intersect(a, b, velocity);
		sf::Vector2f translation;

		if (intersect.willIntersect)
			translation = sf::Vector2f(velocity.x + intersect.minimumTranslationVector.x, velocity.y + intersect.minimumTranslationVector.y);
		else
			translation = velocity;

		if (intersect.willIntersect)
		{
			translation.x = velocity.x + intersect.minimumTranslationVector.x;
			translation.y = velocity.y + intersect.minimumTranslationVector.y;
		}
		
		_a.setFillColor(intersect.intersect ? sf::Color(255, 0, 0, 100):sf::Color(0, 255, 0, 100));
		_b.setFillColor(intersect.intersect ? sf::Color(255, 0, 0, 100):sf::Color(0, 255, 0, 100));

		intersect = math::intersect(a, c, translation);

		if (intersect.willIntersect)
		{
			translation.x += intersect.minimumTranslationVector.x;
			translation.y += intersect.minimumTranslationVector.y;
		}

		a.offset(translation.x, translation.y);
		_a.move(translation.x, translation.y);

		if (_a.getFillColor() != sf::Color(255, 0, 0, 100))
			_a.setFillColor(intersect.intersect ? sf::Color(255, 0, 0, 100):sf::Color(0, 255, 0, 100));

		_c.setFillColor(intersect.intersect ? sf::Color(255, 0, 0, 100):sf::Color(0, 255, 0, 100));
	}
}

void Application::render()
{
	m_window.clear(sf::Color(46, 46, 46));
	m_window.draw(_a);
	m_window.draw(_b);
	m_window.draw(_c);
	m_window.display();
}

