#include "Simulation.h"

// получение времени симуляции в секундах
float getSimulationTime()
{
	oldSimTick = newSimTick;
	QueryPerformanceCounter(&newSimTick);
	return (float(newSimTick.QuadPart - oldSimTick.QuadPart)) / frequency.QuadPart;
}

// симуляция камеры
void cameraSimulation(float simulationTime)
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		camera.leftRight(simulationTime, 0);
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		camera.leftRight(simulationTime, 1);
	}
	if (GetAsyncKeyState(VK_UP))
	{
		camera.upDown(simulationTime, 0);
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		camera.upDown(simulationTime, 1);
	}
	if (GetAsyncKeyState(VK_ADD))
	{
		camera.zoomInOut(simulationTime, 0);
	}
	if (GetAsyncKeyState(VK_SUBTRACT))
	{
		camera.zoomInOut(simulationTime, 1);
	}
}

void gameObjectSimulation(float simulationTime)
{
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (mapObjects[i][j] != nullptr)
			{
				mapObjects[i][j].get()->simulate(simulationTime);
			}
		}
	}

	if (showPlayer)
	{
		player.get()->simulate(simulationTime);
	}

	for (int i = 0; i < 3; i++)
	{
		enemy[i].get()->simulate(simulationTime);

		if (enemy[i].get()->getPositon().x == player.get()->getPositon().x && enemy[i].get()->getPositon().y == player.get()->getPositon().y)
		{
			showPlayer = false;
		}
	}
}

double bombTimer;

void movePlayer()
{
	if (GetAsyncKeyState(65) && !player.get()->isMoving() && passabilityMap[int(player.get()->getPositon().x - 1)][int(player.get()->getPositon().y)] == 0)
	{
		player.get()->move(MoveDirection::LEFT, 1.0f);
	}
	if (GetAsyncKeyState(65) && !player.get()->isMoving() && passabilityMap[int(player.get()->getPositon().x - 1)][int(player.get()->getPositon().y)] == 1
		&& passabilityMap[int(player.get()->getPositon().x - 2)][int(player.get()->getPositon().y)] == 0)
	{
		player.get()->move(MoveDirection::LEFT, 1.0f);
		mapObjects[int(player.get()->getPositon().x - 1)][int(player.get()->getPositon().y)].get()->move(MoveDirection::LEFT, 1.0f);
		mapObjects[int(player.get()->getPositon().x - 2)][int(player.get()->getPositon().y)] = mapObjects[int(player.get()->getPositon().x - 1)][int(player.get()->getPositon().y)];
		mapObjects[int(player.get()->getPositon().x - 1)][int(player.get()->getPositon().y)] = nullptr;
		passabilityMap[int(player.get()->getPositon().x - 1)][int(player.get()->getPositon().y)] = 0;
		passabilityMap[int(player.get()->getPositon().x - 2)][int(player.get()->getPositon().y)] = 1;
	}

	if (GetAsyncKeyState(68) && !player.get()->isMoving() && passabilityMap[int(player.get()->getPositon().x + 1)][int(player.get()->getPositon().y)] == 0)
	{
		player.get()->move(MoveDirection::RIGHT, 1.0f);
	}
	if (GetAsyncKeyState(68) && !player.get()->isMoving() && passabilityMap[int(player.get()->getPositon().x + 1)][int(player.get()->getPositon().y)] == 1
		&& passabilityMap[int(player.get()->getPositon().x + 2)][int(player.get()->getPositon().y)] == 0)
	{
		player.get()->move(MoveDirection::RIGHT, 1.0f);
		mapObjects[int(player.get()->getPositon().x + 1)][int(player.get()->getPositon().y)].get()->move(MoveDirection::RIGHT, 1.0f);
		mapObjects[int(player.get()->getPositon().x + 2)][int(player.get()->getPositon().y)] = mapObjects[int(player.get()->getPositon().x + 1)][int(player.get()->getPositon().y)];
		mapObjects[int(player.get()->getPositon().x + 1)][int(player.get()->getPositon().y)] = nullptr;
		passabilityMap[int(player.get()->getPositon().x + 1)][int(player.get()->getPositon().y)] = 0;
		passabilityMap[int(player.get()->getPositon().x + 2)][int(player.get()->getPositon().y)] = 1;
	}


	if (GetAsyncKeyState(87) && !player.get()->isMoving() && passabilityMap[int(player.get()->getPositon().x)][int(player.get()->getPositon().y - 1)] == 0)
	{
		player.get()->move(MoveDirection::UP, 1.0f);
	}
	if (GetAsyncKeyState(87) && !player.get()->isMoving() && passabilityMap[int(player.get()->getPositon().x)][int(player.get()->getPositon().y - 1)] == 1
		&& passabilityMap[int(player.get()->getPositon().x)][int(player.get()->getPositon().y - 2)] == 0)
	{
		player.get()->move(MoveDirection::UP, 1.0f);
		mapObjects[int(player.get()->getPositon().x)][int(player.get()->getPositon().y - 1)].get()->move(MoveDirection::UP, 1.0f);
		mapObjects[int(player.get()->getPositon().x)][int(player.get()->getPositon().y - 2)] = mapObjects[int(player.get()->getPositon().x)][int(player.get()->getPositon().y - 1)];
		mapObjects[int(player.get()->getPositon().x)][int(player.get()->getPositon().y - 1)] = nullptr;
		passabilityMap[int(player.get()->getPositon().x)][int(player.get()->getPositon().y - 1)] = 0;
		passabilityMap[int(player.get()->getPositon().x)][int(player.get()->getPositon().y - 2)] = 1;
	}


	if (GetAsyncKeyState(83) && !player.get()->isMoving() && passabilityMap[int(player.get()->getPositon().x)][int(player.get()->getPositon().y + 1)] == 0)
	{
		player.get()->move(MoveDirection::DOWN, 1.0f);
	}
	if (GetAsyncKeyState(83) && !player.get()->isMoving() && passabilityMap[int(player.get()->getPositon().x)][int(player.get()->getPositon().y + 1)] == 1
		&& passabilityMap[int(player.get()->getPositon().x)][int(player.get()->getPositon().y + 2)] == 0)
	{
		player.get()->move(MoveDirection::DOWN, 1.0f);
		mapObjects[int(player.get()->getPositon().x)][int(player.get()->getPositon().y + 1)].get()->move(MoveDirection::DOWN, 1.0f);
		mapObjects[int(player.get()->getPositon().x)][int(player.get()->getPositon().y + 2)] = mapObjects[int(player.get()->getPositon().x)][int(player.get()->getPositon().y + 1)];
		mapObjects[int(player.get()->getPositon().x)][int(player.get()->getPositon().y + 1)] = nullptr;
		passabilityMap[int(player.get()->getPositon().x)][int(player.get()->getPositon().y + 1)] = 0;
		passabilityMap[int(player.get()->getPositon().x)][int(player.get()->getPositon().y + 2)] = 1;
	}

	if (GetAsyncKeyState(VK_SPACE) && !player.get()->isMoving() && !bombExist)
	{
		bomb = gameObjectFactory.create(GameObjectType::BOMB, player.get()->getPositon().x, player.get()->getPositon().y);
		bombExist = true;
		bombTimer = 0;
	}
}

void bombSimualtion(float simulationTime)
{
	if (bombTimer >= 2)
	{
		bombExist = false;

		if (bomb != nullptr)
		{
			std::cout << std::endl << bomb.get()->getPositon().x << " " << bomb.get()->getPositon().y;
			
			// 8 декабря 2021 20:44 видит бог я не хотел этого
			if (player.get()->getPositon().x == bomb.get()->getPositon().x && player.get()->getPositon().y == bomb.get()->getPositon().y)
			{
				showPlayer = false;
			}
			if (player.get()->getPositon().x == bomb.get()->getPositon().x - 1 && player.get()->getPositon().y == bomb.get()->getPositon().y)
			{
				showPlayer = false;
			}
			if (player.get()->getPositon().x == bomb.get()->getPositon().x - 2 && player.get()->getPositon().y == bomb.get()->getPositon().y)
			{
				showPlayer = false;
			}
			if (player.get()->getPositon().x == bomb.get()->getPositon().x + 1 && player.get()->getPositon().y == bomb.get()->getPositon().y)
			{
				showPlayer = false;
			}
			if (player.get()->getPositon().x == bomb.get()->getPositon().x + 2 && player.get()->getPositon().y == bomb.get()->getPositon().y)
			{
				showPlayer = false;
			}
			if (player.get()->getPositon().x == bomb.get()->getPositon().x && player.get()->getPositon().y == bomb.get()->getPositon().y + 1)
			{
				showPlayer = false;
			}
			if (player.get()->getPositon().x == bomb.get()->getPositon().x && player.get()->getPositon().y == bomb.get()->getPositon().y + 2)
			{
				showPlayer = false;
			}
			if (player.get()->getPositon().x == bomb.get()->getPositon().x && player.get()->getPositon().y == bomb.get()->getPositon().y - 1)
			{
				showPlayer = false;
			}
			if (player.get()->getPositon().x == bomb.get()->getPositon().x && player.get()->getPositon().y == bomb.get()->getPositon().y - 2)
			{
				showPlayer = false;
			}

			for (int i = 0; i < 21; i++)
			{
				for (int j = 0; j < 21; j++)
				{
					if (mapObjects[i][j] != nullptr)
					{
						if (mapObjects[i][j].get()->getPositon().x == bomb.get()->getPositon().x && mapObjects[i][j].get()->getPositon().y == bomb.get()->getPositon().y && passabilityMap[i][j] == 1)
						{
							mapObjects[i][j] = nullptr;
						}
						else
						{
							if (mapObjects[i][j].get()->getPositon().x == bomb.get()->getPositon().x - 1 && mapObjects[i][j].get()->getPositon().y == bomb.get()->getPositon().y && passabilityMap[i][j] == 1)
							{
								mapObjects[i][j] = nullptr;
							}
							else
							{
								if (mapObjects[i][j].get()->getPositon().x == bomb.get()->getPositon().x - 2 && mapObjects[i][j].get()->getPositon().y == bomb.get()->getPositon().y && passabilityMap[i][j] == 1)
								{
									mapObjects[i][j] = nullptr;
								}
								else
								{
									if (mapObjects[i][j].get()->getPositon().x == bomb.get()->getPositon().x + 1 && mapObjects[i][j].get()->getPositon().y == bomb.get()->getPositon().y && passabilityMap[i][j] == 1)
									{
										mapObjects[i][j] = nullptr;
									}
									else
									{
										if (mapObjects[i][j].get()->getPositon().x == bomb.get()->getPositon().x + 2 && mapObjects[i][j].get()->getPositon().y == bomb.get()->getPositon().y && passabilityMap[i][j] == 1)
										{
											mapObjects[i][j] = nullptr;
										}
										else
										{
											if (mapObjects[i][j].get()->getPositon().x == bomb.get()->getPositon().x && mapObjects[i][j].get()->getPositon().y == bomb.get()->getPositon().y + 1 && passabilityMap[i][j] == 1)
											{
												mapObjects[i][j] = nullptr;
											}
											else
											{
												if (mapObjects[i][j].get()->getPositon().x == bomb.get()->getPositon().x && mapObjects[i][j].get()->getPositon().y == bomb.get()->getPositon().y + 2 && passabilityMap[i][j] == 1)
												{
													mapObjects[i][j] = nullptr;
												}
												else
												{
													if (mapObjects[i][j].get()->getPositon().x == bomb.get()->getPositon().x && mapObjects[i][j].get()->getPositon().y == bomb.get()->getPositon().y - 1 && passabilityMap[i][j] == 1)
													{
														mapObjects[i][j] = nullptr;
													}
													else
													{
														if (mapObjects[i][j].get()->getPositon().x == bomb.get()->getPositon().x && mapObjects[i][j].get()->getPositon().y == bomb.get()->getPositon().y - 2 && passabilityMap[i][j] == 1)
														{
															mapObjects[i][j] = nullptr;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		bomb = nullptr;
		bombTimer = 0;
	}
	else
	{
		bombTimer += simulationTime;
	}
}

void simulation()
{
	// определение времени симуляции
	float simulationTime = getSimulationTime();

	// симуляция камеры
	cameraSimulation(simulationTime);

	// симуляция всех игровых объектов (их плавное перемещение)
	gameObjectSimulation(simulationTime);

	// симуляция монстров
	for (int i = 0; i < 3; i++)
	{
		enemy[i].get()->monsterSimulation();
	}

	// перемещение главного героя
	movePlayer();

	bombSimualtion(simulationTime);

	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
}