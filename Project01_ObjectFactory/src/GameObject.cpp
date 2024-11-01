//#include <GameObject.h>
//
//void GameObject::addComponent(const std::string& name, std::unique_ptr<Component> component) {
//    components[name] = std::move(component);
//}
//
//void GameObject::update() {
//    /*for (auto& [name, component] : components) {
//        component->update();
//    }*/
//    for (auto& pair : components) {
//        auto& component = pair.second;
//        component->update();
//    }
//}
//void GameObject::draw() {
//    /*for (auto& [name, component] : components) {
//        component->draw();
//    }*/
//    for (auto& pair : components) {
//        auto& component = pair.second;
//        component->draw();
//    }
//}