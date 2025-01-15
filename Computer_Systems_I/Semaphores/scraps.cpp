semop(pass_sem,pass_wait_com,1);

  //      AirportAnimator::updateStatus(*planeNum, "BOARD");

        /*if (passNum>=12)
        {
            for(int passenger=1; passenger<=12; passenger++)
            {
                AirportAnimator::updatePassengers(*planeNum, passenger);
                sleep(rand()%2);
                passNum--;
            }
        }*/
/*
        int passenger=1;

        while (passenger<13)
        {
            if (passNum>0)
            {
                AirportAnimator::updatePassengers(*planeNum,passenger);
                sleep(rand()%2);
                passNum--;
                passenger++;
            }
        }*/
        //int passenger=1;

  //      if (passNum>=12)
  //      {
            //int passenger=1;
   //         for(passenger=1; passenger<=12; passenger++)
     //       {
 //               AirportAnimator::updatePassengers(*planeNum, passenger);
 //               sleep(1+rand()%3);
  //              passNum--;
   //         }
            /*
            while (passNum>0 && passenger<=12)
            {
                AirportAnimator::updatePassengers(*planeNum,passenger);
                sleep(rand()%2);
                passNum--;
                passenger++;
            }*/
            //signal

  //      semop(pass_sem, pass_sig_com, 1);


  /*
        struct sembuf deplane_wait_com[1];
        deplane_wait_com[0].sem_num = 0;
        deplane_wait_com[0].sem_op  =-1;
        deplane_wait_com[0].sem_flg = 0;

        struct sembuf deplane_sig_com[1];
        deplane_sig_com[0].sem_num = 0;
        deplane_sig_com[0].sem_op  =1;
        deplane_sig_com[0].sem_flg = 0;
*/
/*
        bool trigger=false;

        while (passenger<=12)
        {
            AirportAnimator::updateStatus(*planeNum, "BOARD");

            if (passNum<=0)
            {
                semop(pass_sem,pass_wait_com,1);
                bool trigger=true;
            }

            AirportAnimator::updatePassengers(*planeNum, passenger);
            sleep(1+rand()%2);
            passNum--;

            if (trigger)
            {
                semop(pass_sem, pass_sig_com, 1);
            }
            passenger++;
        }
*/

//AirportAnimator::updateStatus(*planeNum, "DEPLN");

        //signal here
        /// maybe get rid of
        //semop(pass_sem, pass_sig_com, 1);
