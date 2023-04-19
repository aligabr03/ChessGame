// /*
// Nom: raii.h

// Description: classe implémentant le RAII pour qu’une fonction utilisant cette classe puisse mettre
// temporairement une pièce à un endroit sur l’échiquier,
// et que la pièce s’enlève automatiquement à la destruction de l’instance.

// Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
// Date: 14 Avril 2023
// */

// #ifndef RAII_H
// #define RAII_H

// #endif // RAII_H

// #include "Piece.h"
// #include "stack"

// using namespace model;

// class MoveRecorder
// {
// public:
//     MoveRecorder(std::stack<std::pair<int, int>> &history) : moveHistory(history) {}

//     ~MoveRecorder()
//     {
//         if (!isUndone)
//         {
//             moveHistory.pop();
//         }
//     }

//     void recordMove(std::pair<int, int> move)
//     {
//         moveHistory.push(move);
//         isUndone = false;
//     }

//     void undoMove()
//     {
//         if (moveHistory.empty())
//         {
//             return;
//         }

//         std::pair<int, int> lastMove = moveHistory.top();
//         std::shared_ptr<Piece> movingPiece = view::ChessWindow::movePiece(lastMove.first, lastMove.second);

//         if (movingPiece == nullptr)
//         {
//             return;
//         }

//         movingPiece->setPosition(lastMove.from);

//         if (lastMove.capturedPiece != nullptr)
//         {
//             board->addPiece(lastMove.capturedPiece);
//         }

//         moveHistory.pop();

//         isUndone = true;
//     }

// private:
//     std::stack<std::pair<int, int>> &moveHistory;
//     bool isUndone = false;
// };
