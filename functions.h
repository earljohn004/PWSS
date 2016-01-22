//Global Variables
unsigned char volume_balance[4];

void encodeVolume(int volume)
{
	int temp=0;
	volume_balance[0] = (volume/1000) + 48;
	temp = volume%1000;
	volume_balance[1] = (volume/100) + 48;
	temp = volume%100;
	volume_balance[2] = (temp/10) + 48;
	volume_balance[3] = (temp%10) + 48;

	printf("%s\n",volume_balance);	
}

void decodeVolume(unsigned char *vol)
{
	int voltmp=0;
	
	voltmp=(vol[0]-48)*1000;
	voltmp+=(vol[1]-48)*100;
	voltmp+=(vol[2]-48)*10;
	voltmp+=(vol[3]-48);

	printf("%d\n",voltmp);
}

int  computeCheckSum(unsigned char *packet, int len)
{
	int index;
	int sum = 0;
	for (index = 0; index < len; index++) {
		sum = sum + (int)packet[index];	
	}

	return sum;
}
