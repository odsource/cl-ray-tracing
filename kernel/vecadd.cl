__kernel
void vecadd(__global unsigned char* rendered)
{
        int x = get_global_id(0);
        int y = get_global_id(1);

        rendered[(x + y * 1280) * 3] = 255;
        rendered[(x + y * 1280) * 3 + 1] = 0;
        rendered[(x + y * 1280) * 3 + 2] = 0;
}
