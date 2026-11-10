#include <stdio.h>
#include <string.h>

typedef struct {
    int seq_num;
    int ack_num;
    char data[50];
} Frame;

int main() {
    Frame frame_A_to_B, frame_B_to_A;
    int total_rounds;

    printf("Enter number of bidirectional transmission rounds: ");

    if (scanf("%d", &total_rounds) != 1 ||
        total_rounds <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int seq_A = 0, seq_B = 0;

    printf("\n=== Starting Piggybacking Simulation ===\n");

    for (int i = 1; i <= total_rounds; i++) {

        printf("\n---------- ROUND %d ----------\n", i);

        // Node A sends data to Node B
        frame_A_to_B.seq_num = seq_A;

        frame_A_to_B.ack_num =
            (i == 1) ? -1 : seq_B - 1;

        sprintf(frame_A_to_B.data, "Data_Packet_A%d", i);

        printf("\n[Node A -> Node B] Transmitting Frame:\n");
        printf("- Sequence Number: %d\n",
               frame_A_to_B.seq_num);
        printf("- Data Payload: %s\n",
               frame_A_to_B.data);

        if (frame_A_to_B.ack_num != -1) {
            printf("- Piggybacked ACK: %d\n",
                   frame_A_to_B.ack_num + 1);
        } else {
            printf("- Piggybacked ACK: None (First Frame)\n");
        }

        printf("\n[Node B] Received Frame %d from Node A with data '%s'\n",
               frame_A_to_B.seq_num,
               frame_A_to_B.data);

        // Node B sends data and ACK to Node A
        frame_B_to_A.seq_num = seq_B;
        frame_B_to_A.ack_num = frame_A_to_B.seq_num;

        sprintf(frame_B_to_A.data, "Data_Packet_B%d", i);

        printf("\n[Node B -> Node A] Transmitting Frame (with Piggybacked ACK):\n");
        printf("- Sequence Number: %d\n",
               frame_B_to_A.seq_num);
        printf("- Data Payload: %s\n",
               frame_B_to_A.data);
        printf("- Piggybacked ACK: %d\n",
               frame_B_to_A.ack_num + 1);

        printf("\n[Node A] Received Frame %d from Node B with data '%s'\n",
               frame_B_to_A.seq_num,
               frame_B_to_A.data);

        printf("[Node A] ACK %d extracted successfully!\n",
               frame_B_to_A.ack_num + 1);

        seq_A++;
        seq_B++;
    }

    printf("\n=== Simulation Complete ===\n");

    return 0;
}