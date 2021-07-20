#include "Player.h"
#include <iostream>

// Constructors and Destructors
Player::Player(){}
Player::~Player(){}

// Accessors
/**
 * @brief Returns the position of the top left corner of the player sprite
 * 
 * @return const sf::Vector2f 
 */
const sf::Vector2f Player::getTopLeftPosition() const
{
    return this->sprite.getPosition() - this->sprite.getOrigin();
}
/**
 * @brief Returns the position propery from sprite
 * 
 * @return const sf::Vector2f 
 */
const sf::Vector2f Player::getSpritePosition() const
{
    return this->sprite.getPosition();
}
/**
 * @brief Get the global bounds to check for collision
 * 
 * @return const sf::FloatRect 
 */
const sf::FloatRect Player::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}
const float Player::getHeight() const
{
    return this->getGlobalBounds().height;
}
const float Player::getWidth() const
{
    return this->getGlobalBounds().width;
}
/**
 * @brief Returns the position of the center of the player sprite
 * 
 * @return const sf::Vector2f 
 */
const sf::Vector2f Player::getCenter() const
{
    return sf::Vector2f(this->getTopLeftPosition().x+ this->getWidth()/2,
                         this->getTopLeftPosition().y + this->getHeight()/2);
}
/**
 * @brief get the relative position of origin from the top left corner
 * 
 * @return const sf::Vector2f
 */
const sf::Vector2f Player::getSpriteOrigin() const
{
    return this->sprite.getOrigin();
}
/**
 * @brief Returns the angle of rotation (0 <= angle <360)
 * 
 * @return const float 
 */
const float Player::getRotation() const
{
    return this->sprite.getRotation();
}
// Modifier
/**
 * @brief Set the new absolute position of the top left corner of the Player Sprite
 * 
 * @param x new x coordinate
 * @param y new y coordinate
 */
void Player::setTopLeftPosition(const float x, const float y){
    this->sprite.setPosition(x + this->sprite.getOrigin().x ,
                             y + this->sprite.getOrigin().y);
}
/**
 * @brief sets the Position property of sprite
 * 
 * @param x 
 * @param y 
 */
void Player::setSpritePosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}
/**
 * @brief Set the new absolute position of the center of the Player Sprite
 * 
 * @param x new x coordinate
 * @param y new y coordinate
 */
void Player::setCenter(const float x, const float y){
    this->setTopLeftPosition(x-this->getWidth()/2, y-this->getHeight()/2);
}
/**
 * @brief sets the relative position of origin from the top left corner of the sprite
 * 
 * @param x 
 * @param y 
 */
void Player::setSpriteOrigin(const float x, const float y)
{
    this->sprite.setOrigin(x, y);
}
/**
 * @brief Sets the absolute angle of rotation in clockwise direction
 * 
 * @param angle absolute angle of the final orientation
 */
void Player::setRotation(const float angle)
{
    this->sprite.setRotation(angle);
}
/**
 * @brief Rotates the sprite by given angle clockwise
 * 
 * @param angle angle to rotate the sprite by (clockwise)
 */
void Player::rotate(const float angle)
{
    this->sprite.rotate(angle);
}

//Movement
/**
 * @brief Moves the sprite by given amount
 * 
 * @param dir_x 
 * @param dir_y 
 */
void Player::move(const float dir_x, const float dir_y)
{
    this->sprite.move(dir_x, dir_y);
}
/**
 * @brief For moving the sprite as per velocity in that instant if no rotation is present.
 * Derived classes will override this if rotation or some other new mechanishm is required 
 * 
 * @param elapsedTime Time elapsed between the current and last frame in sf::Time
 */
void Player::updateMovement(sf::Time elapsedTime)
{
    float eTime = elapsedTime.asSeconds();
    float dx = eTime* this->velocity.x;
    float dy = eTime* this->velocity.y;
    //std::cout<<dx<<" "<<dy<<"::"<<sprite.getPosition().x<<" "<<sprite.getPosition().y<<std::endl;
    this->move(dx, dy);
}
/**
 * @brief Sets keyHeld to true if space, up arrow, or left mouse button is held
 * 
 * @param ev 
 */
void Player::handleEvent(sf::Event ev)
{
    static bool spaceHeld{false}, upArrowHeld{false}, leftClickHeld{false};

    switch(ev.type)
    {
        case sf::Event::KeyPressed:
            switch (ev.key.code)
            {
                case sf::Keyboard::Space:
                    spaceHeld = true;
                    break;
                case sf::Keyboard::Up:
                    upArrowHeld = true;
                    break;        
                default:
                    break;
            }
            break;
        case sf::Event::KeyReleased:
            switch (ev.key.code)
            {
                case sf::Keyboard::Space:
                    spaceHeld = false;
                    break;
                case sf::Keyboard::Up:
                    upArrowHeld = false;
                    break;        
                default:
                    break;
            }
            break;
        case sf::Event::MouseButtonPressed:
            switch(ev.key.code)
            {
                case sf::Mouse::Left:
                    leftClickHeld = true;
                default:
                    break;
            }
            break;
        case sf::Event::MouseButtonReleased:
            switch(ev.key.code)
            {
                case sf::Mouse::Left:
                    leftClickHeld = false;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    keyHeld = spaceHeld || upArrowHeld || leftClickHeld;
}
//Update and Render
/**
 * @brief Updates the new position of the player. Calls updateMovement() to move it and 
 * updateVelocity() to change the velocities as per the acceleration.
 * 
 * @param elapsedTime Time elapsed between the current and last frame in sf::Time
 */
void Player::update(sf::Time elapsedTime)
{
    this->updateMovement(elapsedTime);
    this->updateVelocity(elapsedTime);
}
/**
 * @brief Renders the player sprite for each frame
 * 
 * @param target 
 */
void Player::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}
// Functions for class NormalPlayer

