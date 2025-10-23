#include "Garfield/ViewSignal.hh"

#include <TGraph.h>
#include <TH1D.h>
#include <TLegend.h>

#include <cmath>
#include <iostream>

#include "Garfield/Exceptions.hh"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/Sensor.hh"

namespace Garfield {

ViewSignal::ViewSignal() : ViewBase("ViewSignal") {}

ViewSignal::ViewSignal(Sensor* sensor) : ViewSignal() { SetSensor(sensor); }

void ViewSignal::SetSensor(Sensor* sensor) {
  if (!sensor) throw Exception("::SetSensor: Null pointer");
  m_sensor = sensor;
}

void ViewSignal::SetRangeX(const double xmin, const double xmax) {
  if (std::fabs(xmax - xmin) < Small) throw Exception("Invalid range");
  m_xmin = std::min(xmin, xmax);
  m_xmax = std::max(xmin, xmax);
  m_userRangeX = true;
}

void ViewSignal::SetRangeY(const double ymin, const double ymax) {
  if (std::fabs(ymax - ymin) < Small) throw Exception("Invalid range");
  m_ymin = std::min(ymin, ymax);
  m_ymax = std::max(ymin, ymax);
  m_userRangeY = true;
}

TH1* ViewSignal::DrawHistogram(TH1D& h, const std::string& opt,
                               const std::string& ylabel) {
  h.SetDirectory(nullptr);
  h.SetStats(0);
  h.GetXaxis()->SetTitle("time [ns]");
  h.GetYaxis()->SetTitle(ylabel.c_str());
  h.SetLineWidth(5);
  auto hCopy = h.DrawCopy(opt.c_str(), "");
  if (m_userRangeX) hCopy->SetAxisRange(m_xmin, m_xmax, "X");
  if (m_userRangeY) {
    hCopy->SetMinimum(m_ymin);
    hCopy->SetMaximum(m_ymax);
  }
  return hCopy;
}

void ViewSignal::PlotSignal(const std::string& label, const std::string& optT,
                            const std::string& optP, const std::string& optD,
                            const bool same) {
  if (!m_sensor) throw Exception("Sensor is not defined");
  const bool totT = true;
  const bool totP = optP.find("t") != std::string::npos ? true : false;
  const bool totD = optD.find("t") != std::string::npos ? true : false;
  const bool eleT = optT.find("e") != std::string::npos ? true : false;
  const bool eleP = optP.find("e") != std::string::npos ? true : false;
  const bool eleD = optD.find("e") != std::string::npos ? true : false;
  const bool ionT = optT.find("i") != std::string::npos ? true : false;
  const bool ionP = optP.find("i") != std::string::npos ? true : false;
  const bool ionD = optD.find("i") != std::string::npos ? true : false;

  constexpr double tol = 1e-50;

  auto canvas = GetCanvas();
  canvas->cd();
  canvas->SetTitle("Signal");

  std::size_t nBins = 100;
  double t0 = 0., dt = 1.;
  m_sensor->GetTimeWindow(t0, dt, nBins);
  const double t1 = t0 + nBins * dt;

  std::string ylabel = m_labelY;
  if (ylabel.empty()) {
    ylabel = m_sensor->IsIntegrated(label) ? "signal [fC]" : "signal [fC / ns]";
  }
  std::size_t nPlots = same ? 1 : 0;
  if (!RangeSet(gPad)) nPlots = 0;

  TLegend* legend = nullptr;
  if (m_legend) {
    legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->SetHeader("Induced current components");
  }

  if (totT) {
    const auto hname = FindUnusedHistogramName("hSignal_");
    TH1D h(hname.c_str(), "", nBins, t0, t1);
    h.SetLineColor(m_colTotal);
    for (std::size_t i = 0; i < nBins; ++i) {
      const double sig = m_sensor->GetSignal(label, i, 0);
      if (std::isnan(sig) || std::abs(sig) < tol) continue;
      h.SetBinContent(i + 1, sig);
    }
    const std::string opt = nPlots > 0 ? "same" : "";
    ++nPlots;

    // Get and plot threshold crossings.
    const auto nCrossings = m_sensor->GetNumberOfThresholdCrossings();
    if (nCrossings > 0) {
      TGraph gCrossings;
      gCrossings.SetMarkerStyle(20);
      gCrossings.SetMarkerColor(m_colTotal);
      std::vector<double> xp;
      std::vector<double> yp;
      double time = 0., level = 0.;
      bool rise = true;
      for (std::size_t i = 0; i < nCrossings; ++i) {
        if (m_sensor->GetThresholdCrossing(i, time, level, rise)) {
          xp.push_back(time);
          yp.push_back(level);
        }
      }
      gCrossings.DrawGraph(xp.size(), xp.data(), yp.data(), "psame");
    }
    auto hC = DrawHistogram(h, opt, ylabel);
    if (legend) legend->AddEntry(hC, "Total induced signal", "l");
  }

  if (totD) {
    const auto hname = FindUnusedHistogramName("hDelayedSignal_");
    TH1D h(hname.c_str(), "", nBins, t0, t1);
    h.SetLineColor(m_colDelayed[3]);
    h.SetLineStyle(7);
    for (std::size_t i = 0; i < nBins; ++i) {
      const double sig = m_sensor->GetSignal(label, i, 2);
      if (std::isnan(sig) || std::abs(sig) < tol) continue;
      h.SetBinContent(i + 1, sig);
    }
    const std::string opt = nPlots > 0 ? "same" : "";
    ++nPlots;
    auto hC = DrawHistogram(h, opt, ylabel);
    if (legend) legend->AddEntry(hC, "Delayed induced signal", "l");
  }

  if (totP) {
    const auto hname = FindUnusedHistogramName("hPromptSignal_");
    TH1D h(hname.c_str(), "", nBins, t0, t1);
    h.SetLineColor(m_colPrompt[0]);
    h.SetLineStyle(2);
    for (std::size_t i = 0; i < nBins; ++i) {
      const double sig = m_sensor->GetSignal(label, i, 1);
      if (std::isnan(sig) || std::abs(sig) < tol) continue;
      h.SetBinContent(i + 1, sig);
    }
    const std::string opt = nPlots > 0 ? "same" : "";
    ++nPlots;
    auto hC = DrawHistogram(h, opt, ylabel);
    if (legend) legend->AddEntry(hC, "Prompt induced signal", "l");
  }

  if (eleT) {
    const auto hname = FindUnusedHistogramName("hSignalElectrons_");
    TH1D h(hname.c_str(), "", nBins, t0, t1);
    h.SetLineColor(m_colElectrons);
    for (std::size_t i = 0; i < nBins; ++i) {
      const double sig = m_sensor->GetElectronSignal(label, i);
      h.SetBinContent(i + 1, sig);
    }
    const std::string opt = nPlots > 0 ? "same" : "";
    ++nPlots;
    auto hC = DrawHistogram(h, opt, ylabel);
    if (legend) legend->AddEntry(hC, "Electron induced signal", "l");
  }

  if (eleD) {
    const auto hname = FindUnusedHistogramName("hDelayedElectrons_");
    TH1D h(hname.c_str(), "", nBins, t0, t1);
    h.SetLineColor(m_colDelayed[4]);
    h.SetLineStyle(7);
    for (std::size_t i = 0; i < nBins; ++i) {
      const double sig = m_sensor->GetDelayedElectronSignal(label, i);
      if (std::isnan(sig) || std::abs(sig) < tol) continue;
      h.SetBinContent(i + 1, sig);
    }
    const std::string opt = nPlots > 0 ? "same" : "";
    ++nPlots;
    auto hC = DrawHistogram(h, opt, ylabel);
    if (legend) legend->AddEntry(hC, "Electron delayed induced signal", "l");
  }

  if (eleP) {
    const auto hname = FindUnusedHistogramName("hPromptElectrons_");
    TH1D h(hname.c_str(), "", nBins, t0, t1);
    h.SetLineColor(m_colPrompt[1]);
    h.SetLineStyle(2);
    for (std::size_t i = 0; i < nBins; ++i) {
      const double sig = m_sensor->GetElectronSignal(label, i) -
                         m_sensor->GetDelayedElectronSignal(label, i);
      if (std::isnan(sig) || std::abs(sig) < tol) continue;
      h.SetBinContent(i + 1, sig);
    }
    const std::string opt = nPlots > 0 ? "same" : "";
    ++nPlots;
    auto hC = DrawHistogram(h, opt, ylabel);
    if (legend) legend->AddEntry(hC, "Electron prompt induced signal", "l");
  }

  if (ionT) {
    const auto hname = FindUnusedHistogramName("hSignalIons_");
    TH1D h(hname.c_str(), "", nBins, t0, t1);
    h.SetLineColor(m_colIons);
    for (std::size_t i = 0; i < nBins; ++i) {
      const double sig = m_sensor->GetIonSignal(label, i);
      h.SetBinContent(i + 1, sig);
    }
    const std::string opt = nPlots > 0 ? "same" : "";
    ++nPlots;
    auto hC = DrawHistogram(h, opt, ylabel);
    if (legend) legend->AddEntry(hC, "Ion induced signal", "l");
  }

  if (ionD) {
    const auto hname = FindUnusedHistogramName("hDelayedIons_");
    TH1D h(hname.c_str(), "", nBins, t0, t1);
    h.SetLineColor(m_colDelayed[5]);
    h.SetLineStyle(7);
    for (std::size_t i = 0; i < nBins; ++i) {
      const double sig = m_sensor->GetDelayedIonSignal(label, i);
      if (std::isnan(sig) || std::abs(sig) < tol) continue;
      h.SetBinContent(i + 1, sig);
    }
    const std::string opt = nPlots > 0 ? "same" : "";
    ++nPlots;
    auto hC = DrawHistogram(h, opt, ylabel);
    if (legend) legend->AddEntry(hC, "Ion/hole delayed induced signal", "l");
  }

  if (ionP) {
    const auto hname = FindUnusedHistogramName("hPromptIons_");
    TH1D h(hname.c_str(), "", nBins, t0, t1);
    h.SetLineColor(m_colPrompt[2]);
    h.SetLineStyle(2);
    for (std::size_t i = 0; i < nBins; ++i) {
      const double sig = m_sensor->GetIonSignal(label, i) -
                         m_sensor->GetDelayedIonSignal(label, i);
      if (std::isnan(sig) || std::abs(sig) < tol) continue;
      h.SetBinContent(i + 1, sig);
    }
    const std::string opt = nPlots > 0 ? "same" : "";
    ++nPlots;
    auto hC = DrawHistogram(h, opt, ylabel);
    if (legend) legend->AddEntry(hC, "Ion/hole prompt induced signal", "l");
  }

  if (legend) legend->Draw();
  gPad->Update();
}

}  // namespace Garfield
