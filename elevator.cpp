#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace sf;
using namespace std;
class ElevatorSystem {
public:
	class Person {
	public:
		int currentfloor;
		int destinationfloor;
	};

	vector<Person> groundlevel;
	vector<Person> firstlevel;
	vector<Person> secondlevel;
	vector<Person> thirdlevel;
	vector<Person> fourthlevel;
	vector<Person> people_in_elevator;
	vector<Person> elevatorqueue;
	vector<Person> bufor;
	int currentelevetorlevel = 0;
	bool goingup = false;
	bool goingdown = false;




	Person create;

	void check()
	{
		for (auto& floor : elevatorqueue)
		{
			cout << floor.currentfloor << " " << floor.destinationfloor << endl;
		}
	}

	bool is_in_elevator()
	{
		if (people_in_elevator.empty() || elevatorqueue.empty()) {
			return false;
		}

		Person firstElement = elevatorqueue[0];

		for (Person& floor : people_in_elevator) {
			if (floor.currentfloor == firstElement.currentfloor && floor.destinationfloor == firstElement.destinationfloor) {
				return true;
			}
		}

		return false;

	}
	void enter_exit(vector <Person>& whichfloor)
	{


		for (int i = 0; i < people_in_elevator.size(); i++)
		{

			if (people_in_elevator[i].destinationfloor == currentelevetorlevel)
			{

				for (int j = 0; j < elevatorqueue.size(); j++)
				{
					if (people_in_elevator[i].currentfloor == elevatorqueue[j].currentfloor && people_in_elevator[i].destinationfloor == elevatorqueue[j].destinationfloor)
					{
						elevatorqueue.erase(elevatorqueue.begin() + j);
						j--;
						break;
					}
				}
				people_in_elevator.erase(people_in_elevator.begin() + i);
				cout << "Exit " << currentelevetorlevel << endl;
				check();
				i--;
			}
		}

		for (int i = 0; i < whichfloor.size(); i++)
		{

			if (people_in_elevator.size() < 8)
			{
				people_in_elevator.push_back(whichfloor[i]);
				whichfloor.erase(whichfloor.begin() + i);
				i--;
				cout << "Entered " << currentelevetorlevel << endl;
			}
			else
			{
				//postpone();
				break;
			}

		}



	}
	void postpone()
	{
		if (people_in_elevator.size() == 8 && currentelevetorlevel == elevatorqueue[0].currentfloor)
		{
			int the_same = 0;
			do
			{
				if (the_same == 8)
					break;
				the_same++;
				swap(elevatorqueue[0], elevatorqueue[the_same]);
			} while (elevatorqueue[0].currentfloor == elevatorqueue[the_same].currentfloor && elevatorqueue[0].destinationfloor == elevatorqueue[the_same].destinationfloor);
		}
	}
	void direction()
	{
		if (elevatorqueue.size() == 0)
			return;
		if (is_in_elevator())
		{
			if (elevatorqueue[0].destinationfloor > currentelevetorlevel)
			{
				goingup = true;
				goingdown = false;
			}
			else if (elevatorqueue[0].destinationfloor < currentelevetorlevel)
			{
				goingup = false;
				goingdown = true;
			}
		}
		else
		{
			if (elevatorqueue[0].currentfloor > currentelevetorlevel)
			{
				goingup = true;
				goingdown = false;
			}
			else if (elevatorqueue[0].currentfloor < currentelevetorlevel)
			{
				goingup = false;
				goingdown = true;
			}
		}
	}
	void simulation() {

		for (int i = 0; i < elevatorqueue.size(); i++)
			cout << elevatorqueue[i].currentfloor << "  " << elevatorqueue[i].destinationfloor << endl;

		switch (currentelevetorlevel)
		{
		case 0:
			enter_exit(groundlevel);
			break;
		case 1:
			enter_exit(firstlevel);
			break;
		case 2:
			enter_exit(secondlevel);
			break;
		case 3:
			enter_exit(thirdlevel);
			break;
		case 4:
			enter_exit(fourthlevel);
			break;
		}

	}

};
class Button {
public:
	Button(Vector2f position, Vector2f size, Color clickColor, int buttonType, const Font& font);
	bool isMouseOver(RenderWindow& window);
	void draw(RenderWindow& window);
	void updateLabelPosition();
	Button() {}
	RectangleShape shape;
	Vector2f position;
	int buttonType = 0;;
	Text label;
};

Button::Button(Vector2f position, Vector2f size, Color clickColor, int buttonType, const Font& font) {
	shape.setPosition(position);
	shape.setSize(size);
	shape.setFillColor(Color::White);
	shape.setOutlineColor(Color::Black);
	shape.setOutlineThickness(1);
	this->buttonType = buttonType;
	label.setFont(font);
	label.setCharacterSize(30);
	label.setFillColor(Color::Black);
	label.setString(to_string(buttonType));
	updateLabelPosition();
}

bool Button::isMouseOver(RenderWindow& window) {
	Vector2i mousePos = Mouse::getPosition(window);
	Vector2f buttonPos = shape.getPosition();
	Vector2f buttonSize = shape.getSize();

	return (mousePos.x >= buttonPos.x && mousePos.x <= buttonPos.x + buttonSize.x &&
		mousePos.y >= buttonPos.y && mousePos.y <= buttonPos.y + buttonSize.y);
}

void Button::draw(RenderWindow& window) {
	window.draw(shape);
	window.draw(label);
}
void Button::updateLabelPosition() {
	FloatRect textBounds = label.getLocalBounds();
	Vector2f labelPosition(
		shape.getPosition().x + (shape.getSize().x - textBounds.width - 11) / 1.0f,
		shape.getPosition().y + (shape.getSize().y - textBounds.height - 12) / 1.0f
	);
	label.setPosition(labelPosition);
}
void draw_human(RenderWindow& window, int x, int y, int positionm_multiplier, int whichfloor, int destination)
{
	if (whichfloor == 0 || whichfloor == 2 || whichfloor == 4)
		x = x - 32 * (positionm_multiplier);
	else
		x = x + 32 * (positionm_multiplier);

	Color color;
	switch (destination)
	{
	case 0:
		color = Color::Blue;
		break;
	case 1:
		color = Color::Red;
		break;
	case 2:
		color = Color::Cyan;
		break;
	case 3:
		color = Color::Magenta;
		break;
	case 4:
		color = Color::Green;
		break;
	}

	CircleShape head(13);
	head.setFillColor(color);
	head.setPosition(x - 6, y - 26);
	window.draw(head);

	RectangleShape body(Vector2f(15, 50));
	body.setFillColor(color);
	body.setPosition(x, y);
	window.draw(body);

	RectangleShape leftArm(Vector2f(5, 55));
	leftArm.setFillColor(color);
	leftArm.setPosition(x - 6, y);
	window.draw(leftArm);

	RectangleShape rightArm(Vector2f(5, 55));
	rightArm.setFillColor(color);
	rightArm.setPosition(x + 16, y);
	window.draw(rightArm);

	RectangleShape leftLeg(Vector2f(7, 40));
	leftLeg.setFillColor(color);
	leftLeg.setPosition(x, y + 50);
	window.draw(leftLeg);

	RectangleShape RightLeg(Vector2f(7, 40));
	RightLeg.setFillColor(color);
	RightLeg.setPosition(x + 8, y + 50);
	window.draw(RightLeg);
}
void draw_human_floor(RenderWindow& window, int size, int whichfloor, vector<ElevatorSystem::Person>& which)
{
	int destination = 0;

	switch (whichfloor)
	{
	case 0:
		for (int i = 0; i < size; i++)
		{
			destination = which[i].destinationfloor;
			draw_human(window, 375, 626, i, whichfloor, destination);
		}
		break;
	case 1:
		for (int i = 0; i < size; i++)
		{
			destination = which[i].destinationfloor;
			draw_human(window, 695, 456, i, whichfloor, destination);
		}
		break;
	case 2:
		for (int i = 0; i < size; i++)
		{
			destination = which[i].destinationfloor;
			draw_human(window, 375, 326, i, whichfloor, destination);
		}
		break;
	case 3:
		for (int i = 0; i < size; i++)
		{
			destination = which[i].destinationfloor;
			draw_human(window, 695, 186, i, whichfloor, destination);
		}
		break;
	case 4:
		for (int i = 0; i < size; i++)
		{
			destination = which[i].destinationfloor;
			draw_human(window, 375, 46, i, whichfloor, destination);
		}
		break;

	}
}
void draw_human_elevator(RenderWindow& window, int size, vector<ElevatorSystem::Person>& which, float newYH)
{
	int destination = 0;
	for (int i = 0; i < size; i++)
	{
		destination = which[i].destinationfloor;
		draw_human(window, 420, newYH, i, 5, destination);
	}
}
bool want_exit(int currentelevatorlevel, vector<ElevatorSystem::Person>& people_in_elevator)
{
	for (int i = 0; i < people_in_elevator.size(); i++)
	{

		if (people_in_elevator[i].destinationfloor == currentelevatorlevel)
			return true;
	}
	return false;
}
bool want_enter(vector<ElevatorSystem::Person>& which)
{
	if (which.size() != 0)
		return true;
	else
		return false;
}
bool do_stop(int currentelevatorlevel, vector<ElevatorSystem::Person>& people_in_elevator, vector<ElevatorSystem::Person>& which)
{
	if (want_exit(currentelevatorlevel, people_in_elevator))
		return true;
	else
	{
		if (want_enter(which) && people_in_elevator.size() < 8)
			return true;
		else
			return false;
	}
}
int main(int argc, char* argv[])
{

	RenderWindow window(VideoMode(1080, 720), "Elevator Simulator", Style::Close);
	window.setFramerateLimit(60);

	string exePath = argv[0];
	string fontPath = exePath.substr(0, exePath.find_last_of("\\/") + 1) + "arial.ttf";
	Font font;
	if (!font.loadFromFile(fontPath)) {
		return -1;
	}



	RectangleShape rectangle[8];
	rectangle[0].setSize(Vector2f(400, 4));
	rectangle[0].setPosition(Vector2f(0, 716));
	rectangle[0].setFillColor(Color::Blue);
	rectangle[1].setSize(Vector2f(400, 4));
	rectangle[1].setPosition(Vector2f(680, 546));
	rectangle[1].setFillColor(Color::Red);
	rectangle[2].setSize(Vector2f(400, 4));
	rectangle[2].setPosition(Vector2f(0, 416));
	rectangle[2].setFillColor(Color::Cyan);
	rectangle[3].setSize(Vector2f(400, 4));
	rectangle[3].setPosition(Vector2f(680, 276));
	rectangle[3].setFillColor(Color::Magenta);
	rectangle[4].setSize(Vector2f(400, 4));
	rectangle[4].setPosition(Vector2f(0, 136));
	rectangle[4].setFillColor(Color::Green);
	rectangle[5].setSize(Vector2f(4, 720));
	rectangle[5].setPosition(Vector2f(400, 0));
	rectangle[5].setFillColor(Color::Black);
	rectangle[6].setSize(Vector2f(4, 720));
	rectangle[6].setPosition(Vector2f(680, 0));
	rectangle[6].setFillColor(Color::Black);
	rectangle[7].setSize(Vector2f(70, 50));
	rectangle[7].setPosition(Vector2f(720, 50));
	rectangle[7].setOutlineColor(Color::Black);
	rectangle[7].setOutlineThickness(2);
	RectangleShape elevator[4];
	elevator[0].setSize(Vector2f(268, 4));
	elevator[0].setPosition(Vector2f(408, 580));
	elevator[0].setFillColor(Color::Black);
	elevator[1].setSize(Vector2f(268, 4));
	elevator[1].setPosition(Vector2f(408, 716));
	elevator[1].setFillColor(Color::Black);
	elevator[2].setSize(Vector2f(4, 140));
	elevator[2].setPosition(Vector2f(406, 580));
	elevator[2].setFillColor(Color::Black);
	elevator[3].setSize(Vector2f(4, 140));
	elevator[3].setPosition(Vector2f(674, 580));
	elevator[3].setFillColor(Color::Black);


	// Create button
	Button buttons[21];
	buttons[0] = Button(Vector2f(10, 642), Vector2f(30, 30), Color::Red, 1, font);
	buttons[1] = Button(Vector2f(44, 642), Vector2f(30, 30), Color::Red, 2, font);
	buttons[2] = Button(Vector2f(10, 676), Vector2f(30, 30), Color::Red, 3, font);
	buttons[3] = Button(Vector2f(44, 676), Vector2f(30, 30), Color::Red, 4, font);
	buttons[4] = Button(Vector2f(1006, 472), Vector2f(30, 30), Color::Red, 0, font);
	buttons[5] = Button(Vector2f(1040, 472), Vector2f(30, 30), Color::Red, 2, font);
	buttons[6] = Button(Vector2f(1006, 506), Vector2f(30, 30), Color::Red, 3, font);
	buttons[7] = Button(Vector2f(1040, 506), Vector2f(30, 30), Color::Red, 4, font);
	buttons[8] = Button(Vector2f(10, 342), Vector2f(30, 30), Color::Red, 0, font);
	buttons[9] = Button(Vector2f(44, 342), Vector2f(30, 30), Color::Red, 1, font);
	buttons[10] = Button(Vector2f(10, 376), Vector2f(30, 30), Color::Red, 3, font);
	buttons[11] = Button(Vector2f(44, 376), Vector2f(30, 30), Color::Red, 4, font);
	buttons[12] = Button(Vector2f(1006, 202), Vector2f(30, 30), Color::Red, 0, font);
	buttons[13] = Button(Vector2f(1040, 202), Vector2f(30, 30), Color::Red, 1, font);
	buttons[14] = Button(Vector2f(1006, 236), Vector2f(30, 30), Color::Red, 2, font);
	buttons[15] = Button(Vector2f(1040, 236), Vector2f(30, 30), Color::Red, 4, font);
	buttons[16] = Button(Vector2f(10, 62), Vector2f(30, 30), Color::Red, 0, font);
	buttons[17] = Button(Vector2f(44, 62), Vector2f(30, 30), Color::Red, 1, font);
	buttons[18] = Button(Vector2f(10, 96), Vector2f(30, 30), Color::Red, 2, font);
	buttons[19] = Button(Vector2f(44, 96), Vector2f(30, 30), Color::Red, 3, font);

	Clock clock;

	int floor = 0;
	int how_many = 0;
	bool stop = false;
	bool zmiana = false;
	float newYH = 0;
	float newY = 0;


	ElevatorSystem start;
	bool mouseClicked = false;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		window.clear(Color::White);



		//loop through buttons to draw and check for clicks
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (!mouseClicked) {
				bool buttonClicked = false;
				for (int i = 0; i <= 19; ++i) {

					if (buttons[i].isMouseOver(window)) {

						cout << "clicked button: " << i << endl;
						if (Mouse::getPosition(window).y > 0 && Mouse::getPosition(window).y < 136)
						{
							floor = 4;
							start.fourthlevel.push_back({ floor, buttons[i].buttonType });
							how_many = start.fourthlevel.size();
						}
						else if (Mouse::getPosition(window).y > 136 && Mouse::getPosition(window).y < 276)
						{
							floor = 3;
							start.thirdlevel.push_back({ floor, buttons[i].buttonType });
							how_many = start.thirdlevel.size();
						}
						else if (Mouse::getPosition(window).y > 276 && Mouse::getPosition(window).y < 416)
						{
							floor = 2;
							start.secondlevel.push_back({ floor, buttons[i].buttonType });
							how_many = start.secondlevel.size();
						}
						else if (Mouse::getPosition(window).y > 416 && Mouse::getPosition(window).y < 546)
						{
							floor = 1;
							start.firstlevel.push_back({ floor, buttons[i].buttonType });
							how_many = start.firstlevel.size();
						}
						else if (Mouse::getPosition(window).y > 546 && Mouse::getPosition(window).y < 720)
						{
							floor = 0;
							start.groundlevel.push_back({ floor, buttons[i].buttonType });
							how_many = start.groundlevel.size();
						}

						cout << floor << endl;

						start.elevatorqueue.push_back({ floor, buttons[i].buttonType });

						buttonClicked = true;


						start.check();
					}
				}
				if (buttonClicked) {
					mouseClicked = true;
				}
			}
		}
		else {
			mouseClicked = false; // Reset the flag when the mouse button is released
		}

		if (elevator[1].getPosition().y <= 716 && elevator[1].getPosition().y > 546)
		{

			start.currentelevetorlevel = 0;
			if (elevator[1].getPosition().y >= 715 && elevator[1].getPosition().y <= 717)
			{

				if (do_stop(start.currentelevetorlevel, start.people_in_elevator, start.groundlevel))
				{
					sleep(seconds(0.1));
					start.simulation();
					start.postpone();
				}

			}
			start.direction();

		}
		if (elevator[1].getPosition().y <= 546 && elevator[1].getPosition().y > 416)
		{
			start.currentelevetorlevel = 1;
			if (elevator[1].getPosition().y >= 545 && elevator[1].getPosition().y <= 547)
			{
				if (do_stop(start.currentelevetorlevel, start.people_in_elevator, start.firstlevel))
				{
					sleep(seconds(0.1));
					start.simulation();
					start.postpone();
				}

			}
			start.direction();
		}
		if (elevator[1].getPosition().y <= 416 && elevator[1].getPosition().y > 276)
		{
			start.currentelevetorlevel = 2;
			if (elevator[1].getPosition().y >= 415 && elevator[1].getPosition().y <= 417)
			{
				if (do_stop(start.currentelevetorlevel, start.people_in_elevator, start.secondlevel))
				{
					sleep(seconds(0.1));
					start.simulation();
					start.postpone();
				}

			}
			start.direction();

		}
		if (elevator[1].getPosition().y <= 276 && elevator[1].getPosition().y > 136)
		{
			start.currentelevetorlevel = 3;
			if (elevator[1].getPosition().y >= 275 && elevator[1].getPosition().y <= 277)
			{
				if (do_stop(start.currentelevetorlevel, start.people_in_elevator, start.thirdlevel))
				{
					sleep(seconds(0.1));
					start.simulation();
					start.postpone();
				}

			}
			start.direction();

		}
		if (elevator[1].getPosition().y <= 136)
		{
			start.currentelevetorlevel = 4;
			if (elevator[1].getPosition().y >= 135 && elevator[1].getPosition().y <= 137)
			{
				if (do_stop(start.currentelevetorlevel, start.people_in_elevator, start.fourthlevel))
				{
					sleep(seconds(0.1));
					start.simulation();
					start.postpone();
				}

			}
			start.direction();

		}

		float deltaTime = clock.restart().asSeconds();
		float speed = 50.0f;

		if (start.elevatorqueue.size() == 0)
		{
			for (int i = 0; i < 4; ++i) {
				window.draw(elevator[i]);
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				if (start.goingdown)
				{
					newY = elevator[i].getPosition().y + (speed * deltaTime);
					newYH = elevator[i].getPosition().y + (speed * deltaTime) + 46;
				}
				else if (start.goingup)
				{
					newY = elevator[i].getPosition().y - (speed * deltaTime);
					newYH = elevator[i].getPosition().y + 46 - (speed * deltaTime);
				}
				elevator[i].setPosition(elevator[i].getPosition().x, newY);
				window.draw(elevator[i]);
			}
		}

		for (int i = 0; i < 21; ++i) {
			buttons[i].draw(window);
		}
		for (int i = 0; i < 8; ++i) {
			window.draw(rectangle[i]);
		}

		Text text;
		text.setPosition(730, 55);
		text.setFont(font);
		text.setFillColor(Color::Black);
		text.setCharacterSize(30);
		text.setString(to_string(start.people_in_elevator.size() * 70));
		window.draw(text);

		draw_human_floor(window, start.groundlevel.size(), 0, start.groundlevel);
		draw_human_floor(window, start.firstlevel.size(), 1, start.firstlevel);
		draw_human_floor(window, start.secondlevel.size(), 2, start.secondlevel);
		draw_human_floor(window, start.thirdlevel.size(), 3, start.thirdlevel);
		draw_human_floor(window, start.fourthlevel.size(), 4, start.fourthlevel);
		draw_human_elevator(window, start.people_in_elevator.size(), start.people_in_elevator, newYH);

		window.display();

	}

	return 0;
}
