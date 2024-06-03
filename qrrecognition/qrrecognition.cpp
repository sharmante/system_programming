#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 기본 카메라 열기
    VideoCapture cap(0);

    // 카메라가 성공적으로 열렸는지 확인
    if (!cap.isOpened()) {
        cerr << "ERROR: Could not open camera" << endl;
        return 1;
    }

    // QR 코드 감지기
    QRCodeDetector qrDecoder;

    while (true) {
        Mat frame;
        // 카메라에서 새로운 프레임 캡처
        cap >> frame;
        if (frame.empty()) {
            cerr << "ERROR: Could not grab a camera frame" << endl;
            break;
        }

        // QR 코드를 감지하고 디코드
        vector<Point> points;
        string data = qrDecoder.detectAndDecode(frame, points);

        // QR 코드가 감지되면 데이터를 출력
        if (!data.empty()) {
            cout << "QR Code detected: " << data << endl;

            // 감지된 QR 코드 주위에 사각형 그리기
            if (!points.empty()) {
                for (size_t i = 0; i < points.size(); i++) {
                    line(frame, points[i], points[(i + 1) % points.size()], Scalar(255, 0, 0), 3);
                }
            }
        }

        // 프레임 표시
        imshow("QR Code Detection", frame);

        // 사용자가 'q' 키를 누르면 종료
        if (waitKey(1) == 'q') {
            break;
        }
    }

    // 카메라 해제
    cap.release();
    // 모든 OpenCV 창 닫기
    destroyAllWindows();

    return 0;
}