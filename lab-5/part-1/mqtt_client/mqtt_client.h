
void initialize_client(const char* mqtt_broker_ip, const int mqtt_broker_port);

void connect_to_broker();

void subscribe_to_topic(char* topic);

void publish_message(char* topic, char* msg);

void check_connection();
