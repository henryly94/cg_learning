#ifndef GAME_INTERFACE_H_
#define GAME_INTERFACE_H_

namespace cg_learning {
class GameInterface {
protected:
    virtual void tick() = 0;

    virtual void setUp() = 0;

    float frame_interval = 0.01f;
public:
    GameInterface()
    void mainloop() {
        
    };

};

} // namespace cg_learning

#endif // GAME_INTERFACE_H_
