void TTRinv() {
  cout << "TTRinv" << endl;
  Double_t ac[10] = { 1.,0.,0.,2.,0.,13.,4.,0.,23.,77.};
  TRSymMatrix AC(4,ac); cout << "AC\t" << AC << endl;
  TRSymMatrix ACInv(AC, TRArray::kInverted); cout << "AcInv\t" << ACInv << endl;
  Double_t rc[10] = {1.45679,0.,0.,-0.191358,0.,0.1882716,-0.0185185, 0., -0.0462963, 0.02777778};
  TRSymMatrix RC(4, rc); cout << "RC\t" << RC << endl;
}
void TrTest() {
#if 0
  TRMatrix A(3,3," 1 2 3 1 2 3 4 5 6");
  cout << A;
  //  TRSymMatrix S(A,TRArray::kATxA);
  TRSymMatrix S(A,TRArray::kAxAT);
  cout << S;
  TRSymMatrix t1(S,TRArray::kInvertedA);
  cout << t1;
  TRSymMatrix t2(S,TRArray::kInvertedPosDef);
  cout << t2;
  TRSymMatrix t3(S,TRArray::kInverted);
  cout << t3;
  TRMatrix SA(S);
  cout << SA;
  cout << S;
  TRSymMatrix t2(S,TRArray::kInvertedA);  cout << "t2::kInvertedA\t" << t2;
  TRMatrix i2(SA,TRArray::kAxS,t2);      cout << "i2\t" << i2;
  TRSymMatrix t3(S,TRArray::kInvertedPosDef);  cout << "t3::kInvertedPosDef\t" << t3;
  TRMatrix i3(SA,TRArray::kAxS,t3);      cout << "i3\t" << i3;
  TRSymMatrix t1(S,TRArray::kInverted);  cout << "t1::kInverted\t" << t1;
  TRMatrix i1(SA,TRArray::kAxS,t1);      cout << "i1\t" << i1;
#endif
  TTRinv();
}
