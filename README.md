# Tee
Tee c++ implementation
#How to run:
1) Install conan - the simplest way for ubuntu
 - sudo apt install python3-pip
 - pip3 install conan
 - cd (project directory)
2) To install extensions 
 - mkdir build_dir
 - cd build_dir
 - conan config install ../CI/
 - conan install ../CI/conanfile.txt
 
 Now you can build your project