#include"model.h"
#include"shader.h"
class Resume {
private:
	Model resumes[8];
	int current = 0;

public:
	
	Resume() {
		resumes[0] = Model("model\\info/info.obj");
		resumes[1] = Model("model\\skills/skill.obj");
	}
	void Draw(Shader shader)
	{
		resumes[current].Draw(shader);
	}
	void ChangeModel(int n) {
		current = n;
	}
	int getCurrent() { return current; }
};
