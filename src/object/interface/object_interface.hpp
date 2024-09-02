#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <vector>

namespace obj {
    class IObject {
        protected:
            glm::mat4 mModelMatrix;
            glm::vec3 mPosition;
        
            IObject *mpParent = nullptr;
            bool mEnabled = true;
            void updateModelMatrix() {
                glm::mat4 identityMatrix = glm::mat4(1.0f);
                mModelMatrix = glm::translate(identityMatrix, mPosition);
                
                if(mpParent) {
                    mModelMatrix = mpParent->getModelMatrix() * mModelMatrix;
                }
                
                for(auto &child : mChildren) {
                    child->onParentMatrixUpdate();
                }
            }
        
            std::vector<IObject*> mChildren;
        
        public:
            IObject() {
                mChildren = std::vector<IObject*>();
                mModelMatrix = glm::mat4(1.0f);
                mPosition = glm::vec3(0.0f);
            };
        
            IObject(int x, int y, IObject *pParent) {
                mModelMatrix = glm::mat4(1.0f);
                mChildren = std::vector<IObject*>();
                setPosition(x, y);
                setParent(pParent);
            };
        
            ~IObject() {
                if(mpParent) {
                    mpParent->removeChild(this);
                }
            };

            virtual void update() { };
            
            void setParent(IObject *pParent) {
                if(mpParent) {
                    mpParent->removeChild(this);
                }
                mpParent = pParent;
                if(mpParent) {
                    mpParent->addChild(this);
                }
            };
            void setEnabled(bool enabled)  { mEnabled = enabled; };
            void setPosition(glm::vec3 position) {
                mPosition = position;
                updateModelMatrix();
            };
            void setPosition(int x, int y) {
                mPosition = glm::vec3(x, y, 0.0f);
                updateModelMatrix();
            };
            
            glm::vec3 getPosition() { return mPosition; }
            glm::mat4 getModelMatrix() { return mModelMatrix; }
        
            void onParentMatrixUpdate() {
                updateModelMatrix();
            }
        
            void addChild(IObject *pChild) { mChildren.push_back(pChild); }
            void removeChild(IObject *pChild) {
                auto it = std::find(mChildren.begin(), mChildren.end(), pChild);
                if (it != mChildren.end()) {
                    mChildren.erase(it);
                }
            }
        
    };
}
