CXX = g++
CXXFLAGS = `pkg-config --cflags --libs opencv4`
TARGET = qrrecognition

all: $(TARGET)

$(TARGET): qrrecognition.o
	$(CXX) -o $(TARGET) qrrecognition.o $(CXXFLAGS)

qrrecognition.o: qrrecognition.cpp
	$(CXX) -c qrrecognition.cpp $(CXXFLAGS)

clean:
	rm -f $(TARGET) qrrecognition.o