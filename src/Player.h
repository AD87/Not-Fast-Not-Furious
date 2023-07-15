#pragma once
#include "GameObject.h"
#include "EventListener.h"
#include "Mesh.h"
#include "Material.h"
#include "LineSegment.h"
#include "Vec3.h"
#include "OBB.h"
#include "Singleton.h"

class Player : public GameObject, public EventListener, public Uncopyable{
private:
	Player(){}
	friend Singleton<Player>;
public:
	bool load();
	virtual void draw() override;
	virtual void update() override;

	static const char* staticTypeName();
	virtual const char* getTypeName()const override;

	const Vec3& getPos()const;
	float getCarY()const;

	virtual const Box& getBox() const override;
	virtual OBB getOBB() const override;

	void OnKeyboardEvent(const SDL_KeyboardEvent& ke)override;
private:
	void updateCarPos();
	void updateBox();
	void updateMatrix();

	//OBB m_obb;

	float m_wheelX;//wheel rotation on the x axis as degrees
	float m_wheelY;//wheel rotation on the y axis as degrees
	float m_carY;//where the car is facing as degrees
	float m_speed;

	bool m_isForward;
	bool m_isBackward;
	bool m_isLeft;
	bool m_isRight;

	Mesh m_mesh;

	Matrix m_matrix;//matrix used to translate and rotate the player
};

typedef Singleton<Player> ThePlayer;