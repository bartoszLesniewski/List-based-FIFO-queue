#include <iostream>
#include <string>
#include "Queue.h"

void chooseCommand(Queue queue)
{
	int n;
	std::string command;

	while (std::cin >> command)
	{
		if (command == "ADD_BEG")
		{
			std::cin >> n;
			queue.addBeg(n);
		}
		else if (command == "ADD_END")
		{
			std::cin >> n;
			queue.addEnd(n);
		}
		else if (command == "DEL_BEG")
			queue.delBeg();
		else if (command == "DEL_END")
			queue.delEnd();
		else if (command == "PRINT_FORWARD")
			queue.print(Queue::FORWARD);
		else if (command == "PRINT_BACKWARD")
			queue.print(Queue::BACKWARD);

		else if (command == "SIZE")
			queue.size();

		// Komendy do obs³ugi kolejki
		else if (command == "PUSH")
		{
			std::cin >> n;
			queue.push(n);
		}
		else if (command == "POP")
			queue.pop();
		else if (command == "PRINT_QUEUE")
			queue.printQueue();
		else if (command == "COUNT")
			queue.count();
		else if (command == "GARBAGE_SOFT")
			queue.garbage(Queue::SOFT);
		else if (command == "GARBAGE_HARD")
			queue.garbage(Queue::HARD);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(0);
	Queue queue;
	chooseCommand(queue);
}