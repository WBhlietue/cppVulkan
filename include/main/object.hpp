#pragma once

#include <glm/glm.hpp>


namespace seewk::main{
    class Object{
        public:
        void SetPosition(glm::vec2 position){
            x = position.x;
            y = position.y;
        }
        glm::vec2 GetPosition(){
            return glm::vec2(x, y);
        }
        void SetTexture(int id){
            textureID = id;
        }
        int GetTexture(){
            return textureID;
        }
        void SetBorderRadius(int radius){
            borderRadius = radius;
        }
        int GetBorderRadius(){
            return borderRadius;
        }
        void SetSize(glm::vec2 size){
            width = size.x;
            height = size.y;
        
        }
        glm::vec2 GetSize(){
            return glm::vec2(width, height);
        }
        private:
            int x, y;
            int textureID;
            int borderRadius;
            int width, height;

        protected:

    };
}