#include <EthernetFrame/EthernetFrame.h>

class EthernetFrameTest {
    private:
        unsigned char preamble[8];
        unsigned char destinationAddress[6];
        unsigned char sourceAddress[6];
        unsigned char type[2];
        unsigned char fcs[4];
        int payloadSize;

    public:
        EthernetFrameTest() {
            for (int i = 0; i < 8; i++) {
                preamble[i] = 0x55;
            }

            for (int i = 0; i < 6; i++) {
                destinationAddress[i] = 0x00;
                sourceAddress[i] = 0x00;
            }

            destinationAddress[0] = 0x01;

            type[0] = 0x08;
            type[1] = 0x00;

            for (int i = 0; i < 4; i++) {
                fcs[i] = 0x00;
            }

            payloadSize = 0;
        }

        void setUp_test1() {
            for (int i = 0; i < 8; i++) {
                preamble[i] = 0x55;
            }

            for (int i = 0; i < 6; i++) {
                destinationAddress[i] = 0x00;
                sourceAddress[i] = 0x00;
            }

            destinationAddress[0] = 0x01;

            type[0] = 0x08;
            type[1] = 0x00;

            for (int i = 0; i < 4; i++) {
                fcs[i] = 0x00;
            }

            payloadSize = 0;
        }

        void test1() {
            EthernetFrame *ethernetFrame = new EthernetFrame(preamble, destinationAddress, sourceAddress, type, fcs, payloadSize);

            assert(ethernetFrame->getPayloadSize() == 0);

            delete ethernetFrame;
        }
};